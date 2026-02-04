// Конфигурация для LilyGo T-Embed CC1101
// Устройство НЕ ИМЕЕТ touch-экрана!

#ifndef _T_EMBED_CC1101_CONFIG_H
#define _T_EMBED_CC1101_CONFIG_H

// Отключаем все touch-функции
#undef HAS_TOUCH
#undef TOUCH_CS
#undef TOUCH_IRQ

// Основные параметры дисплея
#define DISPLAY_ST7789
#define DISPLAY_WIDTH 170
#define DISPLAY_HEIGHT 320
#define DISPLAY_ROTATION 0

// SPI дисплея
#define TFT_CS 41
#define TFT_DC 16
#define TFT_RST 40
#define TFT_BL 21

// Нет тачскрина!
#define TOUCH_CS -1
#define TOUCH_IRQ -1

#endif // _T_EMBED_CC1101_CONFIG_H
