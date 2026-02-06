#include "DisplayManager_ST7789.h"
#include <Arduino.h>

DisplayManager_ST7789::DisplayManager_ST7789() 
    : tft(&SPI, TFT_CS, TFT_DC, TFT_RST) {}

bool DisplayManager_ST7789::begin() {
    // Инициализация SPI с правильными пинами
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    
    // Инициализация дисплея
    tft.init(SCREEN_HEIGHT, SCREEN_WIDTH); // 170x320, но нужно повернуть
    
    // Устанавливаем ориентацию (3 = 270 градусов для 320x170)
    tft.setRotation(3);
    
    // Включаем дисплей
    tft.fillScreen(ST77XX_BLACK);
    
    // Настройка подсветки (если отдельный пин)
    if(TFT_BL >= 0) {
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH); // Включаем подсветку
    }
    
    // Устанавливаем стандартный шрифт и цвет
    tft.setTextWrap(false);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    
    Serial.println("[DISPLAY] ST7789 initialized: 320x170");
    return true;
}

void DisplayManager_ST7789::setBrightness(uint8_t level) {
    if(TFT_BL >= 0) {
        // ESP32-S3 ШИМ на пине 14 (если это подсветка)
        analogWrite(TFT_BL, level);
    }
}

void DisplayManager_ST7789::clear(uint32_t color) {
    tft.fillScreen(color);
}

void DisplayManager_ST7789::drawText(int16_t x, int16_t y, const String& text, 
                                     uint32_t color, uint8_t size) {
    tft.setTextColor(color);
    tft.setTextSize(size);
    tft.setCursor(x, y);
    tft.print(text);
}

void DisplayManager_ST7789::drawCenteredText(int16_t y, const String& text, 
                                            uint32_t color, uint8_t size) {
    tft.setTextColor(color);
    tft.setTextSize(size);
    
    // Расчет позиции для центрирования
    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    int16_t x = (SCREEN_WIDTH - w) / 2;
    
    tft.setCursor(x, y);
    tft.print(text);
}

void DisplayManager_ST7789::drawHeader(const String& title) {
    // Фон заголовка
    tft.fillRect(0, 0, SCREEN_WIDTH, 30, ST77XX_BLUE);
    
    // Текст заголовка
    drawCenteredText(10, title, ST77XX_WHITE, 2);
    
    // Разделительная линия
    tft.drawFastHLine(0, 31, SCREEN_WIDTH, ST77XX_WHITE);
}

void DisplayManager_ST7789::drawProgressBar(int16_t x, int16_t y, uint16_t w, 
                                           uint16_t h, float progress, uint32_t color) {
    // Ограничиваем прогресс
    if(progress < 0) progress = 0;
    if(progress > 1) progress = 1;
    
    // Рамка
    tft.drawRect(x, y, w, h, ST77XX_WHITE);
    
    // Заполнение
    uint16_t fillWidth = (uint16_t)((w - 2) * progress);
    if(fillWidth > 0) {
        tft.fillRect(x + 1, y + 1, fillWidth, h - 2, color);
    }
}

void DisplayManager_ST7789::drawBruteforceStatus(uint32_t current, uint32_t found,
                                                uint32_t attempts, float progress, 
                                                const String& state) {
    clear(ST77XX_BLACK);
    drawHeader("BRUCE RF BRUTEFORCER");
    
    int16_t y_pos = 40;
    
    // Протокол
    drawText(10, y_pos, "Protocol: Rolling Code", ST77XX_CYAN, 1);
    y_pos += 20;
    
    // Текущий ключ
    char buf[64];
    snprintf(buf, sizeof(buf), "Current: 0x%08X", current);
    drawText(10, y_pos, buf, ST77XX_YELLOW, 1);
    y_pos += 20;
    
    // Найденный ключ
    if(found > 0) {
        snprintf(buf, sizeof(buf), "Found: 0x%08X (SUCCESS!)", found);
        drawText(10, y_pos, buf, ST77XX_GREEN, 1);
    } else {
        drawText(10, y_pos, "Found: None", ST77XX_RED, 1);
    }
    y_pos += 20;
    
    // Попытки
    snprintf(buf, sizeof(buf), "Attempts: %u", attempts);
    drawText(10, y_pos, buf, ST77XX_WHITE, 1);
    y_pos += 25;
    
    // Прогресс
    drawText(10, y_pos, "Progress:", ST77XX_WHITE, 1);
    drawProgressBar(80, y_pos, 220, 15, progress, ST77XX_GREEN);
    y_pos += 25;
    
    // Статус
    String status = "State: " + state;
    drawCenteredText(y_pos, status, 
                    (state == "RUNNING") ? ST77XX_GREEN : 
                    (state == "PAUSED") ? ST77XX_YELLOW : ST77XX_ORANGE, 1);
}

void DisplayManager_ST7789::drawMenu(const String items[], uint8_t count, 
                                    uint8_t selected) {
    clear(ST77XX_BLACK);
    drawHeader("MENU");
    
    int16_t y_start = 40;
    int16_t item_height = 25;
    
    for(uint8_t i = 0; i < count; i++) {
        int16_t y = y_start + i * item_height;
        
        if(i == selected) {
            // Выделенный элемент
            tft.fillRoundRect(5, y - 3, SCREEN_WIDTH - 10, item_height - 4, 5, ST77XX_BLUE);
            drawText(15, y, "> " + items[i], ST77XX_WHITE, 1);
        } else {
            // Обычный элемент
            drawText(15, y, "  " + items[i], ST77XX_WHITE, 1);
        }
    }
}

void DisplayManager_ST7789::drawButton(int16_t x, int16_t y, uint16_t w, 
                                      uint16_t h, const String& label, bool pressed) {
    uint32_t bgColor = pressed ? ST77XX_DARKGREY : ST77XX_BLUE;
    uint32_t textColor = pressed ? ST77XX_BLACK : ST77XX_WHITE;
    
    // Кнопка
    tft.fillRoundRect(x, y, w, h, 8, bgColor);
    tft.drawRoundRect(x, y, w, h, 8, ST77XX_WHITE);
    
    // Текст (примерное центрирование)
    int16_t textX = x + (w - label.length() * 6) / 2;
    int16_t textY = y + (h - 8) / 2;
    drawText(textX, textY, label, textColor, 1);
}

void DisplayManager_ST7789::setTheme(const DisplayTheme& theme) {
    currentTheme = theme;
    // Применяем настройки темы
    if(TFT_BL >= 0) {
        setBrightness(theme.brightness);
    }
    // Инверсия цветов
    tft.invertDisplay(theme.inverted);
}

void DisplayManager_ST7789::drawFooter(const String& status) {
    int16_t footerY = SCREEN_HEIGHT - 20;
    tft.fillRect(0, footerY, SCREEN_WIDTH, 20, ST77XX_DARKGREY);
    drawCenteredText(footerY + 5, status, ST77XX_WHITE, 1);
}
