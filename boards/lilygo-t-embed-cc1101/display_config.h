// Display configuration OVERRIDE for LilyGo T-Embed CC1101
// This device has NO touch screen!

#ifndef _T_EMBED_DISPLAY_CONFIG_H
#define _T_EMBED_DISPLAY_CONFIG_H

// Force disable touch for T-Embed
#undef HAS_TOUCH
#undef TOUCH_CS
#undef TOUCH_IRQ

// Explicitly define no touch
#define HAS_TOUCH 0
#define TOUCH_CS -1
#define TOUCH_IRQ -1

// Display type
#define DISPLAY_ST7789
#define DISPLAY_WIDTH 170
#define DISPLAY_HEIGHT 320

// SPI pins (from official T-Embed documentation)
#define TFT_CS   41
#define TFT_DC   16
#define TFT_RST  40
#define TFT_BL   21
#define TFT_MOSI 9
#define TFT_SCLK 11
#define TFT_MISO -1

#endif // _T_EMBED_DISPLAY_CONFIG_H
