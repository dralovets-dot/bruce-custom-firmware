#pragma once

// Конфигурация шрифта для T-Embed CC1101
// Увеличенные шрифты для лучшей читаемости

#ifndef FONT_SCALE_H
#define FONT_SCALE_H

// Базовые размеры из Bruce
#ifndef FM
#define FM 2
#endif

#ifndef FP  
#define FP 4  
#endif

// Коэффициент увеличения (2 = в 2 раза больше)
#define FONT_SCALE_FACTOR 2

// Масштабированные версии
#define FM_SCALED (FM * FONT_SCALE_FACTOR)
#define FP_SCALED (FP * FONT_SCALE_FACTOR)

// Удобные макросы
#define SET_LARGE_FONT() tft.setTextSize(FP_SCALED)
#define SET_MEDIUM_FONT() tft.setTextSize(FM_SCALED)
#define SET_SMALL_FONT() tft.setTextSize(1 * FONT_SCALE_FACTOR)

#endif // FONT_SCALE_H
