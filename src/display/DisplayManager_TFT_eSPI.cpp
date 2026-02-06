#include "DisplayManager_TFT_eSPI.h"
#include <Arduino.h>

DisplayManager_TFT_eSPI::DisplayManager_TFT_eSPI() {
    // Конструктор
}

bool DisplayManager_TFT_eSPI::begin() {
    // Как в официальном примере: поднимаем CS перед инициализацией
    pinMode(TFT_CS_PIN, OUTPUT);
    digitalWrite(TFT_CS_PIN, HIGH);
    
    // Инициализация дисплея
    tft.init();
    tft.setRotation(3);  // Поворот как в официальном примере
    tft.fillScreen(TFT_BLACK);
    
    Serial.println("[DISPLAY] TFT_eSPI initialized for T-Embed");
    return true;
}

void DisplayManager_TFT_eSPI::clear(uint32_t color) {
    tft.fillScreen(color);
}

void DisplayManager_TFT_eSPI::drawText(int16_t x, int16_t y, const String& text, 
                                      uint32_t color, uint8_t size) {
    tft.setTextColor(color);
    tft.setTextSize(size);
    tft.setCursor(x, y);
    tft.print(text);
}

// ИСПРАВЛЕНО: Убираем getTextBounds, используем простой расчет
void DisplayManager_TFT_eSPI::drawCenteredText(int16_t y, const String& text, 
                                              uint32_t color, uint8_t size) {
    tft.setTextColor(color);
    tft.setTextSize(size);
    
    // Простой расчет: примерная ширина символа = 6*size, высота = 8*size
    int16_t textWidth = text.length() * 6 * size;
    int16_t textHeight = 8 * size;
    
    // Центрируем по горизонтали, вертикальная позиция задается y
    int16_t x = (SCREEN_WIDTH - textWidth) / 2;
    tft.setCursor(x, y);
    tft.print(text);
}

void DisplayManager_TFT_eSPI::drawProgressBar(int16_t x, int16_t y, uint16_t w, 
                                             uint16_t h, float progress, uint32_t color) {
    if (progress < 0) progress = 0;
    if (progress > 1) progress = 1;
    
    tft.drawRect(x, y, w, h, TFT_WHITE);
    uint16_t fillWidth = (uint16_t)((w - 2) * progress);
    if (fillWidth > 0) {
        tft.fillRect(x + 1, y + 1, fillWidth, h - 2, color);
    }
}

void DisplayManager_TFT_eSPI::drawBruteforceStatus(uint32_t current, uint32_t found,
                                                  uint32_t attempts, float progress, 
                                                  const String& state) {
    clear(TFT_BLACK);
    
    drawCenteredText(10, "BRUCE RF BRUTEFORCE", TFT_GREEN);
    
    int16_t y_pos = 40;
    char buf[64];
    
    snprintf(buf, sizeof(buf), "Protocol: Rolling Code");
    drawText(10, y_pos, buf, TFT_CYAN); y_pos += 20;
    
    snprintf(buf, sizeof(buf), "Current: 0x%08X", current);
    drawText(10, y_pos, buf, TFT_YELLOW); y_pos += 20;
    
    if (found > 0) {
        snprintf(buf, sizeof(buf), "Found: 0x%08X", found);
        drawText(10, y_pos, buf, TFT_GREEN);
    } else {
        drawText(10, y_pos, "Found: None", TFT_RED);
    }
    y_pos += 20;
    
    snprintf(buf, sizeof(buf), "Attempts: %u", attempts);
    drawText(10, y_pos, buf, TFT_WHITE); y_pos += 25;
    
    drawText(10, y_pos, "Progress:", TFT_WHITE);
    drawProgressBar(80, y_pos, 220, 15, progress, TFT_BLUE);
    y_pos += 25;
    
    String status = "State: " + state;
    uint32_t statusColor = TFT_ORANGE;
    if (state == "RUNNING") statusColor = TFT_GREEN;
    if (state == "PAUSED") statusColor = TFT_YELLOW;
    
    drawCenteredText(y_pos, status, statusColor);
}

void DisplayManager_TFT_eSPI::drawMenu(const String items[], uint8_t count, 
                                      uint8_t selected) {
    clear(TFT_BLACK);
    drawCenteredText(10, "BRUCE RF MENU", TFT_GREEN);
    
    int16_t y_start = 40;
    
    for (uint8_t i = 0; i < count; i++) {
        int16_t y = y_start + i * 25;
        
        if (i == selected) {
            tft.fillRect(5, y - 3, SCREEN_WIDTH - 10, 20, TFT_BLUE);
            drawText(15, y, "> " + items[i], TFT_WHITE);
        } else {
            drawText(15, y, "  " + items[i], TFT_WHITE);
        }
    }
}

// ИСПРАВЛЕНО: Упрощаем drawButton без getTextBounds
void DisplayManager_TFT_eSPI::drawButton(int16_t x, int16_t y, uint16_t w, uint16_t h, 
                                        const String& label, bool pressed) {
    uint32_t bgColor = pressed ? TFT_DARKGREY : TFT_BLUE;
    uint32_t textColor = pressed ? TFT_BLACK : TFT_WHITE;
    
    tft.fillRoundRect(x, y, w, h, 8, bgColor);
    tft.drawRoundRect(x, y, w, h, 8, TFT_WHITE);
    
    // Простое центрирование текста (приблизительное)
    tft.setTextColor(textColor);
    tft.setTextSize(1);
    
    // Примерная ширина текста
    int16_t textWidth = label.length() * 6;
    int16_t textHeight = 8;
    
    int16_t textX = x + (w - textWidth) / 2;
    int16_t textY = y + (h - textHeight) / 2;
    
    tft.setCursor(textX, textY);
    tft.print(label);
}

void DisplayManager_TFT_eSPI::setBrightness(uint8_t level) {
    (void)level; // Заглушка
}

void DisplayManager_TFT_eSPI::setTheme(const DisplayTheme& theme) {
    currentTheme = theme;
}

// Убираем неработающий метод getTextBounds
void DisplayManager_TFT_eSPI::getTextBounds(const String& text, int16_t* x, int16_t* y, 
                                          uint16_t* w, uint16_t* h, uint8_t size) {
    // Упрощенная реализация
    *w = text.length() * 6 * size;
    *h = 8 * size;
    *x = 0;
    *y = 0;
}
