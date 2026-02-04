#pragma once

// Конфигурация масштаба шрифта для Bruce
// Простая система увеличения шрифта

#ifndef FONT_SCALE_H
#define FONT_SCALE_H

#include <TFT_eSPI.h>

// Базовые размеры шрифтов (оригинальные значения из Bruce)
#ifndef FM
#define FM 2  // Medium font
#endif

#ifndef FP  
#define FP 4  // Large font  
#endif

// Коэффициент увеличения шрифта
// 1 = оригинал, 2 = в 2 раза больше
#define FONT_SCALE_FACTOR 2

// Масштабированные версии
#define FM_SCALED (FM * FONT_SCALE_FACTOR)
#define FP_SCALED (FP * FONT_SCALE_FACTOR)

#endif // FONT_SCALE_H
