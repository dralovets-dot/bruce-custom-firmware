#include "tftespi.h"

// Minimal implementation to bypass compilation errors

void tft_display::init() { TFT_eSPI::init(); }
void tft_display::setRotation(uint8_t r) { TFT_eSPI::setRotation(r); }
uint8_t tft_display::getRotation() { return TFT_eSPI::getRotation(); }
void tft_display::fillScreen(uint32_t c) { TFT_eSPI::fillScreen(c); }
void tft_display::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t c) { TFT_eSPI::fillRect(x, y, w, h, c); }
void tft_display::fillCircle(int32_t x, int32_t y, int32_t r, uint32_t c) { TFT_eSPI::fillCircle(x, y, r, c); }
void tft_display::fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t c) { TFT_eSPI::fillEllipse(x, y, rx, ry, c); }
void tft_display::drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t c) { TFT_eSPI::drawFastHLine(x, y, w, c); }
void tft_display::drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t c) { TFT_eSPI::drawFastVLine(x, y, h, c); }
void tft_display::setTextFont(uint8_t f) { TFT_eSPI::setTextFont(f); }
void tft_display::setTextColor(uint16_t c, uint16_t b) { TFT_eSPI::setTextColor(c, b); }
void tft_display::setTextSize(uint8_t s) { TFT_eSPI::setTextSize(s); }
void tft_display::setTextWrap(bool w) { TFT_eSPI::setTextWrap(w); }
void tft_display::setCursor(int16_t x, int16_t y) { TFT_eSPI::setCursor(x, y); }
void tft_display::print(const char *t) { TFT_eSPI::print(t); }
int16_t tft_display::textWidth(const char *t) { return TFT_eSPI::textWidth(t); }
int16_t tft_display::fontHeight() { return TFT_eSPI::fontHeight(); }
void tft_display::pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint8_t *d) { TFT_eSPI::pushImage(x, y, w, h, const_cast<uint8_t*>(d)); }
void tft_display::startWrite() { TFT_eSPI::startWrite(); }
void tft_display::endWrite() { TFT_eSPI::endWrite(); }
TFT_eSPI *tft_display::native() { return static_cast<TFT_eSPI *>(this); }

tft_sprite::tft_sprite(tft_display *p) : TFT_eSprite(p ? p->native() : nullptr) {}
void *tft_sprite::createSprite(int16_t w, int16_t h, uint8_t f) { return TFT_eSprite::createSprite(w, h, f); }
void tft_sprite::deleteSprite() { TFT_eSprite::deleteSprite(); }
void tft_sprite::setColorDepth(uint8_t d) { TFT_eSprite::setColorDepth(d); }
void tft_sprite::fillScreen(uint32_t c) { TFT_eSprite::fillSprite(c); }
void tft_sprite::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t c) { TFT_eSprite::fillRect(x, y, w, h, c); }
void tft_sprite::fillCircle(int32_t x, int32_t y, int32_t r, uint32_t c) { TFT_eSprite::fillCircle(x, y, r, c); }
void tft_sprite::fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t c) { TFT_eSprite::fillEllipse(x, y, rx, ry, c); }
void tft_sprite::drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t c) { TFT_eSprite::drawFastHLine(x, y, w, c); }
void tft_sprite::drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t c) { TFT_eSprite::drawFastVLine(x, y, h, c); }
void tft_sprite::pushSprite(int32_t x, int32_t y, uint32_t t) { TFT_eSprite::pushSprite(x, y, t); }
void tft_sprite::pushToSprite(tft_sprite *d, int32_t x, int32_t y, uint32_t t) { TFT_eSprite::pushToSprite(d->nativeSprite(), x, y, t); }
void tft_sprite::setTextFont(uint8_t f) { TFT_eSprite::setTextFont(f); }
void tft_sprite::setTextColor(uint16_t c, uint16_t b) { TFT_eSprite::setTextColor(c, b); }
void tft_sprite::setTextSize(uint8_t s) { TFT_eSprite::setTextSize(s); }
void tft_sprite::setTextWrap(bool w) { TFT_eSprite::setTextWrap(w); }
void tft_sprite::setCursor(int16_t x, int16_t y) { TFT_eSprite::setCursor(x, y); }
void tft_sprite::print(const char *t) { TFT_eSprite::print(t); }
int16_t tft_sprite::textWidth(const char *t) { return TFT_eSprite::textWidth(t); }
int16_t tft_sprite::fontHeight() { return TFT_eSprite::fontHeight(); }
TFT_eSprite *tft_sprite::nativeSprite() { return static_cast<TFT_eSprite *>(this); }
