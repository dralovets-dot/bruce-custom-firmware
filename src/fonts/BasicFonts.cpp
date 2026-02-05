#include "Fonts.h"

namespace Fonts {
    // Простой шрифт 5x7 (ASCII 32-126)
    const uint8_t smallFont5x7[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, // Space
        0x00, 0x00, 0x5F, 0x00, 0x00, // !
        0x00, 0x07, 0x00, 0x07, 0x00, // "
        // ... остальные глифы
    };
    
    const FontInfo smallFontInfo = {
        smallFont5x7,
        5,    // width
        7,    // height
        32,   // firstChar
        126,  // lastChar
        1     // spacing
    };
    
    // Функции для работы со шрифтами
    const uint8_t* getFontGlyph(const FontInfo& fontInfo, char c) {
        if (c < fontInfo.firstChar || c > fontInfo.lastChar) {
            c = '?'; // Заменяем неизвестные символы на '?'
        }
        uint8_t index = c - fontInfo.firstChar;
        return &fontInfo.data[index * fontInfo.width];
    }
    
    uint8_t getCharWidth(const FontInfo& fontInfo, char c) {
        return fontInfo.width + fontInfo.spacing;
    }
    
    uint8_t getTextWidth(const FontInfo& fontInfo, const String& text) {
        uint8_t width = 0;
        for (uint8_t i = 0; i < text.length(); i++) {
            width += getCharWidth(fontInfo, text[i]);
        }
        return width;
    }
}
