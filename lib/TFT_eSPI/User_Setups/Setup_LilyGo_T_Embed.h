// Configuration for LilyGo T-Embed CC1101 with ST7789 320x170
// Based on official example: display_test.ino

#define USER_SETUP_INFO "LilyGo T-Embed CC1101"

#define ST7789_DRIVER
#define TFT_WIDTH  320
#define TFT_HEIGHT 170

// ESP32-S3 pins for T-Embed (from example)
#define TFT_CS   10  // Chip select control pin
#define TFT_DC   14  // Data Command control pin
#define TFT_RST  -1  // Reset pin (-1 if not used)
#define TFT_BL   14  // LED back-light control pin

// SPI configuration
#define TFT_SPI_PORT 1
#define SPI_FREQUENCY  40000000
#define SPI_READ_FREQUENCY  20000000

// Color definitions
#define TFT_BLACK       0x0000
#define TFT_WHITE       0xFFFF
#define TFT_RED         0xF800
#define TFT_GREEN       0x07E0
#define TFT_BLUE        0x001F
#define TFT_CYAN        0x07FF
#define TFT_MAGENTA     0xF81F
#define TFT_YELLOW      0xFFE0
#define TFT_ORANGE      0xFD20
#define TFT_GRAY        0x8410
#define TFT_LIGHTGREY   0xD69A

// Font options
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SMOOTH_FONT
