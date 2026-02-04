#ifndef TFTESPI_H
#define TFTESPI_H

#include <TFT_eSPI.h>

class TFTESPI : public TFT_eSPI {
public:
    TFTESPI() : TFT_eSPI() {}

    // Drawing functions
    using TFT_eSPI::drawRGBBitmap;
    using TFT_eSPI::fillRect;
    using TFT_eSPI::fillScreen;
    using TFT_eSPI::drawRect;
    using TFT_eSPI::drawCircle;
    using TFT_eSPI::fillCircle;
    using TFT_eSPI::drawLine;
    using TFT_eSPI::drawPixel;
    using TFT_eSPI::drawFastVLine;
    using TFT_eSPI::drawFastHLine;

    // Text functions
    using TFT_eSPI::setCursor;
    using TFT_eSPI::setTextColor;
    using TFT_eSPI::setTextSize;
    using TFT_eSPI::print;
    using TFT_eSPI::drawCentreString;
    using TFT_eSPI::drawString;
    using TFT_eSPI::setTextDatum;

// ВАЖНО: touch-функции только если определен HAS_TOUCH
#if defined(HAS_TOUCH) && HAS_TOUCH == 1
    // Touch functions
    using TFT_eSPI::calibrateTouch;
    using TFT_eSPI::getTouch;
    using TFT_eSPI::getTouchRaw;
    using TFT_eSPI::setTouch;
    using TFT_eSPI::convertRawXY;
#endif

    // For backwards compatibility
    void fillWindow(uint16_t color) {
        fillScreen(color);
    }

    void drawWindowLine(int16_t x, int16_t y, int16_t w, uint16_t *buffer) {
        pushImage(x, y, w, 1, buffer);
    }
};

#endif // TFTESPI_H
