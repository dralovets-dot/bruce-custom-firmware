#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>
#include <vector>
#include <map>

class DisplayManager {
public:
    enum FontStyle {
        FONT_SMALL = 0,
        FONT_MEDIUM,
        FONT_LARGE,
        FONT_MONO,
        FONT_BOLD,
        FONT_CUSTOM_1,
        FONT_CUSTOM_2,
        FONT_CUSTOM_3
    };
    
    struct DisplayTheme {
        uint32_t backgroundColor;
        uint32_t textColor;
        uint32_t highlightColor;
        uint32_t buttonColor;
        uint32_t borderColor;
        uint8_t brightness;
        bool inverted;
    };
    
    DisplayManager();
    ~DisplayManager();
    
    void begin();
    void update();
    
    void setFont(FontStyle font);
    void setTheme(const DisplayTheme& theme);
    void loadCustomFont(const uint8_t* fontData, size_t size, FontStyle slot);
    
    void drawText(int x, int y, const String& text, FontStyle font = FONT_MEDIUM);
    void drawProgressBar(int x, int y, int width, int height, float progress);
    void drawBruteforceStatus(uint32_t currentKey, uint32_t foundKey, 
                             uint32_t attempts, float progress, const char* state);
    void drawMenu(const std::vector<String>& items, int selectedIndex);
    void drawButton(int x, int y, int width, int height, const String& label, bool pressed = false);
    
    void clear();
    void refresh();
    
private:
    void initDisplay();
    void loadDefaultFonts();
    void applyTheme();
    
    FontStyle currentFont = FONT_MEDIUM;
    DisplayTheme currentTheme;
    bool displayInitialized = false;
    
    // Указатели на текущие шрифты
    const uint8_t* smallFont = nullptr;
    const uint8_t* mediumFont = nullptr;
    const uint8_t* largeFont = nullptr;
    const uint8_t* monoFont = nullptr;
    const uint8_t* boldFont = nullptr;
    
    // Пользовательские шрифты
    std::map<FontStyle, const uint8_t*> customFonts;
    
    void drawChar(int x, int y, char c, const uint8_t* font);
    int getCharWidth(char c, const uint8_t* font);
    int getTextWidth(const String& text, const uint8_t* font);
    int getFontHeight(const uint8_t* font);
};

#endif // DISPLAY_MANAGER_H
