#pragma once
#include <Adafruit_ST7789.h>
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

class DisplayManager_ST7789 {
private:
    Adafruit_ST7789 tft;
    static const uint16_t SCREEN_WIDTH = 320;
    static const uint16_t SCREEN_HEIGHT = 170;
    
    // ПРАВИЛЬНЫЕ ПИНЫ для T-Embed CC1101 (ESP32-S3)
    // На основе типичной конфигурации LilyGO
    static const int8_t TFT_CS = 10;      // Chip Select
    static const int8_t TFT_DC = 14;      // Data/Command
    static const int8_t TFT_RST = -1;     // -1 если подключен к RST или не используется
    static const int8_t TFT_BL = 14;      // Backlight (часто совмещен с DC)
    
    // SPI пины для ESP32-S3
    static const int8_t SPI_MOSI = 11;    // GPIO11
    static const int8_t SPI_MISO = 13;    // GPIO13  
    static const int8_t SPI_SCK = 12;     // GPIO12
    
    DisplayTheme currentTheme;
    
public:
    DisplayManager_ST7789();
    bool begin();
    void setBrightness(uint8_t level);
    void setTheme(const DisplayTheme& theme);
    void clear(uint32_t color = 0x0000);
    
    // Текст
    void drawText(int16_t x, int16_t y, const String& text, 
                  uint32_t color = 0xFFFF, uint8_t size = 2);
    
    // Графика
    void drawProgressBar(int16_t x, int16_t y, uint16_t w, uint16_t h, 
                        float progress, uint32_t color = 0x07E0);
    
    // Интерфейс Bruce
    void drawBruteforceStatus(uint32_t current, uint32_t found, 
                             uint32_t attempts, float progress, const String& state);
    
    void drawMenu(const String items[], uint8_t count, uint8_t selected);
    void drawButton(int16_t x, int16_t y, uint16_t w, uint16_t h, 
                   const String& label, bool pressed = false);
    
    void refresh() { /* ST7789 автоматически обновляется */ }
    
    // Вспомогательные методы
    void drawCenteredText(int16_t y, const String& text, uint32_t color = 0xFFFF, uint8_t size = 2);
    void drawHeader(const String& title);
    void drawFooter(const String& status);
};
