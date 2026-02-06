#pragma once
#include <TFT_eSPI.h>
#include <SPI.h>

struct DisplayTheme {
    uint32_t backgroundColor;
    uint32_t textColor;
    uint32_t highlightColor;
    uint32_t buttonColor;
    uint32_t borderColor;
    uint8_t brightness;
    bool inverted;
};

class DisplayManager_TFT_eSPI {
private:
    TFT_eSPI tft;
    static const uint16_t SCREEN_WIDTH = 320;
    static const uint16_t SCREEN_HEIGHT = 170;
    
    // Пины как в официальном примере
    static const int8_t TFT_CS_PIN = 10;
    static const int8_t TFT_DC_PIN = 14;
    
    DisplayTheme currentTheme;
    
public:
    DisplayManager_TFT_eSPI();
    bool begin();
    void setBrightness(uint8_t level);
    void setTheme(const DisplayTheme& theme);
    void clear(uint32_t color = TFT_BLACK);
    
    // Текст
    void drawText(int16_t x, int16_t y, const String& text, 
                  uint32_t color = TFT_WHITE, uint8_t size = 2);
    
    void drawCenteredText(int16_t y, const String& text, 
                         uint32_t color = TFT_WHITE, uint8_t size = 2);
    
    // Графика
    void drawProgressBar(int16_t x, int16_t y, uint16_t w, uint16_t h, 
                        float progress, uint32_t color = TFT_BLUE);
    
    // Интерфейс Bruce
    void drawBruteforceStatus(uint32_t current, uint32_t found, 
                             uint32_t attempts, float progress, const String& state);
    
    void drawMenu(const String items[], uint8_t count, uint8_t selected);
    void drawButton(int16_t x, int16_t y, uint16_t w, uint16_t h, 
                   const String& label, bool pressed = false);
    
    void refresh() { /* TFT_eSPI обновляется автоматически */ }
    
    // Вспомогательные методы
    void drawHeader(const String& title);
    void drawFooter(const String& status);
    
    // Получить размеры текста
    void getTextBounds(const String& text, int16_t* x, int16_t* y, 
                      uint16_t* w, uint16_t* h, uint8_t size = 2);
};
