#include "DisplayManager_TFT_eSPI.h"
#include <Arduino.h>

DisplayManager_TFT_eSPI::DisplayManager_TFT_eSPI() {
    // Конструктор - инициализация происходит в begin()
}

bool DisplayManager_TFT_eSPI::begin() {
    // Пины CS и DC уже определены в Setup_LilyGo_T_Embed.h
    // TFT_eSPI автоматически читает настройки из User_Setups/
    
    // Важно: как в примере, поднимаем CS перед инициализацией
    pinMode(TFT_CS_PIN, OUTPUT);
    digitalWrite(TFT_CS_PIN, HIGH);
    
    // Инициализация дисплея
    tft.init();
    tft.setRotation(3);  // Поворот как в официальном примере
    tft.fillScreen(TFT_BLACK);
    
    // Отключаем подсветку если она мешает (позже настроим)
    // pinMode(TFT_BL, OUTPUT);
    // digitalWrite(TFT_BL, HIGH);
    
    Serial.println("[DISPLAY] TFT_eSPI initialized for T-Embed");
    Serial.println("[DISPLAY] Resolution: 320x170, Rotation: 3");
    
    return true;
}

void DisplayManager_TFT_eSPI::setBrightness(uint8_t level) {
    // T-Embed может не иметь отдельного пина подсветки
    // Или он совмещён с DC (пин 14)
    // Пока оставляем заглушку
    (void)level; // Используем параметр чтобы избежать warning
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

void DisplayManager_TFT_eSPI::drawCenteredText(int16_t y, const String& text, 
                                              uint32_t color, uint8_t size) {
    tft.setTextColor(color);
    tft.setTextSize(size);
    
    // Получаем размеры текста
    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    
    // Центрируем
    int16_t x = (SCREEN_WIDTH - w) / 2;
    tft.setCursor(x, y);
    tft.print(text);
}

void DisplayManager_TFT_eSPI::drawProgressBar(int16_t x, int16_t y, uint16_t w, 
                                             uint16_t h, float progress, uint32_t color) {
    // Ограничиваем прогресс
    if (progress < 0) progress = 0;
    if (progress > 1) progress = 1;
    
    // Рамка
    tft.drawRect(x, y, w, h, TFT_WHITE);
    
    // Заполнение
    uint16_t fillWidth = (uint16_t)((w - 2) * progress);
    if (fillWidth > 0) {
        tft.fillRect(x + 1, y + 1, fillWidth, h - 2, color);
    }
}

void DisplayManager_TFT_eSPI::drawBruteforceStatus(uint32_t current, uint32_t found,
                                                  uint32_t attempts, float progress, 
                                                  const String& state) {
    clear(TFT_BLACK);
    
    // Заголовок
    drawCenteredText(10, "BRUCE RF BRUTEFORCE", TFT_GREEN, 2);
    
    int16_t y_pos = 40;
    
    // Протокол
    drawText(10, y_pos, "Protocol: Rolling Code", TFT_CYAN, 1);
    y_pos += 20;
    
    // Ключи
    char buf[64];
    snprintf(buf, sizeof(buf), "Current: 0x%08X", current);
    drawText(10, y_pos, buf, TFT_YELLOW, 1);
    y_pos += 20;
    
    // Найденный ключ
    if (found > 0) {
        snprintf(buf, sizeof(buf), "Found: 0x%08X (SUCCESS!)", found);
        drawText(10, y_pos, buf, TFT_GREEN, 1);
    } else {
        drawText(10, y_pos, "Found: None", TFT_RED, 1);
    }
    y_pos += 20;
    
    // Попытки
    snprintf(buf, sizeof(buf), "Attempts: %u", attempts);
    drawText(10, y_pos, buf, TFT_WHITE, 1);
    y_pos += 25;
    
    // Прогресс
    drawText(10, y_pos, "Progress:", TFT_WHITE, 1);
    drawProgressBar(80, y_pos, 220, 15, progress, TFT_BLUE);
    y_pos += 25;
    
    // Статус
    String status = "State: " + state;
    uint32_t statusColor = TFT_ORANGE;
    if (state == "RUNNING") statusColor = TFT_GREEN;
    if (state == "PAUSED") statusColor = TFT_YELLOW;
    
    drawCenteredText(y_pos, status, statusColor, 1);
}

void DisplayManager_TFT_eSPI::drawMenu(const String items[], uint8_t count, 
                                      uint8_t selected) {
    clear(TFT_BLACK);
    
    // Заголовок меню
    drawCenteredText(10, "BRUCE RF MENU", TFT_GREEN, 2);
    
    int16_t y_start = 40;
    int16_t item_height = 25;
    
    for (uint8_t i = 0; i < count; i++) {
        int16_t y = y_start + i * item_height;
        
        if (i == selected) {
            // Выделенный элемент
            tft.fillRoundRect(5, y - 3, SCREEN_WIDTH - 10, item_height - 4, 5, TFT_BLUE);
            drawText(15, y, "> " + items[i], TFT_WHITE, 1);
        } else {
            // Обычный элемент
            drawText(15, y, "  " + items[i], TFT_WHITE, 1);
        }
    }
}

void DisplayManager_TFT_eSPI::drawButton(int16_t x, int16_t y, uint16_t w, uint16_t h, 
                                        const String& label, bool pressed) {
    uint32_t bgColor = pressed ? TFT_DARKGREY : TFT_BLUE;
    uint32_t textColor = pressed ? TFT_BLACK : TFT_WHITE;
    
    // Кнопка
    tft.fillRoundRect(x, y, w, h, 8, bgColor);
    tft.drawRoundRect(x, y, w, h, 8, TFT_WHITE);
    
    // Текст (центрирование)
    tft.setTextColor(textColor);
    tft.setTextSize(1);
    
    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    tft.getTextBounds(label, 0, 0, &x1, &y1, &textWidth, &textHeight);
    
    int16_t textX = x + (w - textWidth) / 2;
    int16_t textY = y + (h - textHeight) / 2;
    
    tft.setCursor(textX, textY);
    tft.print(label);
}

void DisplayManager_TFT_eSPI::setTheme(const DisplayTheme& theme) {
    currentTheme = theme;
    // Для TFT_eSPI просто сохраняем тему
    // Реальная реализация зависит от возможностей библиотеки
}

void DisplayManager_TFT_eSPI::drawHeader(const String& title) {
    tft.fillRect(0, 0, SCREEN_WIDTH, 30, TFT_BLUE);
    drawCenteredText(10, title, TFT_WHITE, 2);
    tft.drawFastHLine(0, 31, SCREEN_WIDTH, TFT_WHITE);
}

void DisplayManager_TFT_eSPI::drawFooter(const String& status) {
    int16_t footerY = SCREEN_HEIGHT - 20;
    tft.fillRect(0, footerY, SCREEN_WIDTH, 20, TFT_DARKGREY);
    drawCenteredText(footerY + 5, status, TFT_WHITE, 1);
}

void DisplayManager_TFT_eSPI::getTextBounds(const String& text, int16_t* x, int16_t* y, 
                                          uint16_t* w, uint16_t* h, uint8_t size) {
    tft.setTextSize(size);
    tft.getTextBounds(text, 0, 0, x, y, w, h);
}
