#ifndef FONTS_H
#define FONTS_H

#include <Arduino.h>

namespace Fonts {
    // Маленький шрифт 5x7
    extern const uint8_t smallFont5x7[];
    
    // Средний шрифт 8x13
    extern const uint8_t mediumFont8x13[];
    
    // Большой шрифт 12x16
    extern const uint8_t largeFont12x16[];
    
    // Моноширинный шрифт 6x10
    extern const uint8_t monoFont6x10[];
    
    // Жирный шрифт 8x13 bold
    extern const uint8_t boldFont8x13[];
    
    // Структура информации о шрифте
    struct FontInfo {
        const uint8_t* data;
        uint8_t width;
        uint8_t height;
        uint8_t firstChar;
        uint8_t lastChar;
        uint8_t spacing;
    };
    
    // Информация о доступных шрифтах
    extern const FontInfo smallFontInfo;
    extern const FontInfo mediumFontInfo;
    extern const FontInfo largeFontInfo;
    extern const FontInfo monoFontInfo;
    extern const FontInfo boldFontInfo;
    
    // Функции для работы со шрифтами
    const uint8_t* getFontGlyph(const FontInfo& fontInfo, char c);
    uint8_t getCharWidth(const FontInfo& fontInfo, char c);
    uint8_t getTextWidth(const FontInfo& fontInfo, const String& text);
    void drawChar(uint16_t x, uint16_t y, char c, const FontInfo& fontInfo, 
                  uint16_t color, uint16_t bgColor, void(*drawPixel)(int, int, uint16_t));
    void drawText(uint16_t x, uint16_t y, const String& text, const FontInfo& fontInfo,
                  uint16_t color, uint16_t bgColor, void(*drawPixel)(int, int, uint16_t));
}

#endif // FONTS_H
