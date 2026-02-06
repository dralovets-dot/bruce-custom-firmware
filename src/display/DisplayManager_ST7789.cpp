#include "DisplayManager_ST7789.h"
#include <Arduino.h>

DisplayManager_ST7789::DisplayManager_ST7789() 
    : tft(&SPI, TFT_CS, TFT_DC, TFT_RST) {}

bool DisplayManager_ST7789::begin() {
    SPI.begin(12, 13, 11);
    tft.init(SCREEN_HEIGHT, SCREEN_WIDTH);
    tft.setRotation(3);
    tft.fillScreen(ST77XX_BLACK);
    
    if(TFT_BL >= 0) {
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH);
    }
    
    return true;
}

void DisplayManager_ST7789::setBrightness(uint8_t level) {
    if(TFT_BL >= 0) {
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

void DisplayManager_ST7789::drawProgressBar(int16_t x, int16_t y, uint16_t w, 
                                           uint16_t h, float progress, uint32_t color) {
    tft.drawRect(x, y, w, h, ST77XX_WHITE);
    uint16_t fillWidth = (uint16_t)((w - 2) * progress);
    if(fillWidth > 0) {
        tft.fillRect(x + 1, y + 1, fillWidth, h - 2, color);
    }
}

void DisplayManager_ST7789::drawBruteforceStatus(uint32_t current, uint32_t found,
                                                uint32_t attempts, float progress, 
                                                const String& state) {
    clear(ST77XX_BLACK);
    
    drawText(10, 10, "BRUCE RF BRUTEFORCE", ST77XX_GREEN, 2);
    drawText(10, 40, "Protocol: Rolling Code", ST77XX_WHITE, 1);
    
    char buf[50];
    snprintf(buf, sizeof(buf), "Current: 0x%08X", current);
    drawText(10, 70, buf, ST77XX_YELLOW, 1);
    
    snprintf(buf, sizeof(buf), "Found: 0x%08X", found);
    drawText(10, 90, buf, found ? ST77XX_GREEN : ST77XX_RED, 1);
    
    snprintf(buf, sizeof(buf), "Attempts: %u", attempts);
    drawText(10, 110, buf, ST77XX_CYAN, 1);
    
    drawText(10, 130, "Progress:", ST77XX_WHITE, 1);
    drawProgressBar(80, 130, 200, 15, progress, ST77XX_BLUE);
    
    drawText(10, 150, "State: " + state, 
             state == "RUNNING" ? ST77XX_GREEN : ST77XX_ORANGE, 1);
}

void DisplayManager_ST7789::drawMenu(const String items[], uint8_t count, 
                                    uint8_t selected) {
    clear(ST77XX_BLACK);
    drawText(10, 10, "BRUCE RF MENU", ST77XX_GREEN, 2);
    
    for(uint8_t i = 0; i < count; i++) {
        int16_t y = 40 + i * 25;
        if(i == selected) {
            tft.fillRect(5, y - 5, 310, 20, ST77XX_BLUE);
            drawText(10, y, "> " + items[i], ST77XX_WHITE, 1);
        } else {
            drawText(10, y, "  " + items[i], ST77XX_WHITE, 1);
        }
    }
}

void DisplayManager_ST7789::drawButton(int16_t x, int16_t y, uint16_t w, 
                                      uint16_t h, const String& label, bool pressed) {
    // Используем доступные цвета: при нажатии - темно-серый (0x3186), иначе синий
    uint32_t bgColor = pressed ? 0x3186 : ST77XX_BLUE;
    uint32_t textColor = pressed ? ST77XX_BLACK : ST77XX_WHITE;
    
    tft.fillRoundRect(x, y, w, h, 5, bgColor);
    tft.drawRoundRect(x, y, w, h, 5, ST77XX_WHITE);
    
    int16_t textX = x + (w - label.length() * 6 * 1) / 2;
    int16_t textY = y + (h - 8 * 1) / 2;
    drawText(textX, textY, label, textColor, 1);
}

void DisplayManager_ST7789::setTheme(const DisplayTheme& theme) {
    currentTheme = theme;
    tft.invertDisplay(theme.inverted);
    setBrightness(theme.brightness);
}
