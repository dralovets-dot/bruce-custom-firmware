# Создайте исправленную версию
#include "tftespi.h"

// ============ tft_display ============

void tft_display::init() {
    TFT_eSPI::init();
}

void tft_display::setRotation(uint8_t rotation) {
    TFT_eSPI::setRotation(rotation);
}

uint8_t tft_display::getRotation() {
    return TFT_eSPI::getRotation();
}

void tft_display::fillScreen(uint32_t color) {
    TFT_eSPI::fillScreen(color);
}

void tft_display::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color) {
    TFT_eSPI::fillRect(x, y, w, h, color);
}

void tft_display::fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color) {
    TFT_eSPI::fillCircle(x, y, r, color);
}

void tft_display::fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color) {
    TFT_eSPI::fillEllipse(x, y, rx, ry, color);
}

void tft_display::drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color) {
    TFT_eSPI::drawFastHLine(x, y, w, color);
}

void tft_display::drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color) {
    TFT_eSPI::drawFastVLine(x, y, h, color);
}

void tft_display::setTextFont(uint8_t font) {
    TFT_eSPI::setTextFont(font);
}

void tft_display::setTextColor(uint16_t color, uint16_t bgcolor) {
    TFT_eSPI::setTextColor(color, bgcolor);
}

void tft_display::setTextSize(uint8_t size) {
    TFT_eSPI::setTextSize(size);
}

void tft_display::setTextWrap(bool wrap) {
    TFT_eSPI::setTextWrap(wrap);
}

void tft_display::setCursor(int16_t x, int16_t y) {
    TFT_eSPI::setCursor(x, y);
}

void tft_display::print(const char *text) {
    TFT_eSPI::print(text);
}

int16_t tft_display::textWidth(const char *text) {
    return TFT_eSPI::textWidth(text);
}

int16_t tft_display::fontHeight() {
    return TFT_eSPI::fontHeight();
}

void tft_display::pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint8_t *data) {
    TFT_eSPI::pushImage(x, y, w, h, const_cast<uint8_t*>(data));
}

void tft_display::startWrite() {
    TFT_eSPI::startWrite();
}

void tft_display::endWrite() {
    TFT_eSPI::endWrite();
}

TFT_eSPI *tft_display::native() {
    return static_cast<TFT_eSPI *>(this);
}

// ============ tft_sprite ============

tft_sprite::tft_sprite(tft_display *parent) 
    : TFT_eSprite(parent ? parent->native() : nullptr) {}

void *tft_sprite::createSprite(int16_t w, int16_t h, uint8_t frames) {
    return TFT_eSprite::createSprite(w, h, frames);
}

void tft_sprite::deleteSprite() {
    TFT_eSprite::deleteSprite();
}

void tft_sprite::setColorDepth(uint8_t depth) {
    TFT_eSprite::setColorDepth(depth);
}

void tft_sprite::fillScreen(uint32_t color) {
    TFT_eSprite::fillSprite(color);
}

void tft_sprite::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color) {
    TFT_eSprite::fillRect(x, y, w, h, color);
}

void tft_sprite::fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color) {
    TFT_eSprite::fillCircle(x, y, r, color);
}

void tft_sprite::fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color) {
    TFT_eSprite::fillEllipse(x, y, rx, ry, color);
}

void tft_sprite::drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color) {
    TFT_eSprite::drawFastHLine(x, y, w, color);
}

void tft_sprite::drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color) {
    TFT_eSprite::drawFastVLine(x, y, h, color);
}

void tft_sprite::pushSprite(int32_t x, int32_t y, uint32_t transparent) {
    TFT_eSprite::pushSprite(x, y, transparent);
}

void tft_sprite::pushToSprite(tft_sprite *dest, int32_t x, int32_t y, uint32_t transparent) {
    TFT_eSprite::pushToSprite(dest->nativeSprite(), x, y, transparent);
}

void tft_sprite::setTextFont(uint8_t font) {
    TFT_eSprite::setTextFont(font);
}

void tft_sprite::setTextColor(uint16_t color, uint16_t bgcolor) {
    TFT_eSprite::setTextColor(color, bgcolor);
}

void tft_sprite::setTextSize(uint8_t size) {
    TFT_eSprite::setTextSize(size);
}

void tft_sprite::setTextWrap(bool wrap) {
    TFT_eSprite::setTextWrap(wrap);
}

void tft_sprite::setCursor(int16_t x, int16_t y) {
    TFT_eSprite::setCursor(x, y);
}

void tft_sprite::print(const char *text) {
    TFT_eSprite::print(text);
}

int16_t tft_sprite::textWidth(const char *text) {
    return TFT_eSprite::textWidth(text);
}

int16_t tft_sprite::fontHeight() {
    return TFT_eSprite::fontHeight();
}

TFT_eSprite *tft_sprite::nativeSprite() {
    return static_cast<TFT_eSprite *>(this);
}
