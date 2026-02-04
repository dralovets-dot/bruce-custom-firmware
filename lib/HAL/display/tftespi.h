#ifndef LIB_HAL_TFTESPI_H
#define LIB_HAL_TFTESPI_H
#include <pins_arduino.h>
#ifdef USE_TFT_ESPI
#include <TFT_eSPI.h>

#include "tft_defines.h"
class tft_display : private TFT_eSPI {
public:
    explicit tft_display(int16_t _W = TFT_WIDTH, int16_t _H = TFT_HEIGHT);
    friend class tft_sprite;
    friend class tft_logger;

    using TFT_eSPI::begin;
    using TFT_eSPI::color565;
    using TFT_eSPI::drawArc;
    using TFT_eSPI::drawCentreString;
    using TFT_eSPI::drawCircle;
    using TFT_eSPI::drawEllipse;
    using TFT_eSPI::drawFastHLine;
    using TFT_eSPI::drawFastVLine;
    using TFT_eSPI::drawLine;
    using TFT_eSPI::drawPixel;
    using TFT_eSPI::drawRect;
    using TFT_eSPI::drawRightString;
    using TFT_eSPI::drawRoundRect;
    using TFT_eSPI::drawString;
    using TFT_eSPI::drawTriangle;
    using TFT_eSPI::drawWideLine;
    using TFT_eSPI::drawXBitmap;
    using TFT_eSPI::fillCircle;
    using TFT_eSPI::fillEllipse;
    using TFT_eSPI::fillRect;
    using TFT_eSPI::fillRectHGradient;
    using TFT_eSPI::fillRectVGradient;
    using TFT_eSPI::fillRoundRect;
    using TFT_eSPI::fillScreen;
    using TFT_eSPI::fillTriangle;
    using TFT_eSPI::fontHeight;
    using TFT_eSPI::getCursorX;
    using TFT_eSPI::getCursorY;
    using TFT_eSPI::getSwapBytes;
    using TFT_eSPI::getTextDatum;
    using TFT_eSPI::height;
    using TFT_eSPI::init;
    using TFT_eSPI::invertDisplay;
    using TFT_eSPI::print;
    using TFT_eSPI::printf;
    using TFT_eSPI::println;
    using TFT_eSPI::pushImage;
    using TFT_eSPI::setCursor;
    using TFT_eSPI::setRotation;
    using TFT_eSPI::setSwapBytes;
    using TFT_eSPI::setTextColor;
    using TFT_eSPI::setTextDatum;
    using TFT_eSPI::setTextFont;
    using TFT_eSPI::setTextSize;
    using TFT_eSPI::setTextWrap;
    using TFT_eSPI::sleep;
    using TFT_eSPI::textWidth;
    using TFT_eSPI::width;
    using TFT_eSPI::write;
    using TFT_eSPI::writecommand;

// ВАЖНОЕ ИСПРАВЛЕНИЕ: Touch функции ТОЛЬКО если определен TOUCH_CS
// И добавляем дополнительную проверку для T-Embed
#ifdef TOUCH_CS
#if TOUCH_CS > 0  // Дополнительная проверка: touch только если CS пин определен (>0)
#if !defined(TFT_PARALLEL_8_BIT) && !defined(RP2040_PIO_INTERFACE) && !defined(TFT_PARALLEL_16_BIT)
    // Touchscreen Functions
    using TFT_eSPI::calibrateTouch;
    using TFT_eSPI::getTouch;
    using TFT_eSPI::getTouchRaw;
    using TFT_eSPI::setTouch;
#endif
#endif
#endif

#if !defined(TFT_PARALLEL_8_BIT) && !defined(TFT_PARALLEL_16_BIT)
    using TFT_eSPI::getSPIinstance;
#endif
    uint32_t getTextColor() const;
    uint32_t getTextBgColor() const;
    uint8_t getTextSize() const;
    void setTextSize(uint8_t s);
    void setTextFont(uint8_t f);
    void setTextColor(uint32_t c);
    void setTextColor(uint32_t c, uint32_t bg);
    void setTextBgColor(uint32_t c);
    void fillWindow(uint16_t color);
    void drawWindowLine(int16_t x, int16_t y, int16_t w, uint16_t *buffer);
    void reset(int x, int y, uint32_t fc, int size, uint32_t bg, uint32_t screen);
};

#endif // USE_TFT_ESPI
#endif // LIB_HAL_TFTESPI_H
