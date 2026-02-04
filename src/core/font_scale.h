#pragma once

// Конфигурация масштаба шрифта для Bruce
// Простая система увеличения шрифта

#ifndef FONT_SCALE_H
#define FONT_SCALE_H

// Коэффициент увеличения шрифта
// 1 = оригинал, 2 = в 2 раза больше
#define FONT_SCALE_FACTOR 2

// Функция для получения увеличенного размера шрифта
static inline int getScaledTextSize(int baseSize) {
    return baseSize * FONT_SCALE_FACTOR;
}

// Макрос для удобного использования
#define SET_SCALED_TEXT_SIZE(size) tft.setTextSize(getScaledTextSize(size))

#endif // FONT_SCALE_H
