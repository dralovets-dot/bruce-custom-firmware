// LilyGo T-Embed CC1101 pin definitions
// NOTE: This device has NO TOUCH SCREEN!

#ifndef PINS_ARDUINO_H
#define PINS_ARDUINO_H

#include <stdint.h>

#define EXTERNAL_NUM_INTERRUPTS 16
#define NUM_DIGITAL_PINS        40
#define NUM_ANALOG_INPUTS       16

// SPI
#define BOARD_SPI_SCK  11
#define BOARD_SPI_MOSI 9
#define BOARD_SPI_MISO 10

// I2C
#define BOARD_I2C_SDA  8
#define BOARD_I2C_SCL  18

// Display (ST7789, NO TOUCH!)
#define DISPLAY_WIDTH  170
#define DISPLAY_HEIGHT 320
#define DISPLAY_BL   21
#define DISPLAY_CS   41
#define DISPLAY_DC   16
#define DISPLAY_RST  40
#define DISPLAY_MOSI 9
#define DISPLAY_SCLK 11

// УБИРАЕМ ВСЕ TOUCH ОПРЕДЕЛЕНИЯ!
// #define TOUCH_CS  -1  // НЕТ ТАЧСКРИНА!
// #define TOUCH_IRQ -1  // НЕТ ТАЧСКРИНА!

// Encoder
#define ENCODER_INA 4
#define ENCODER_INB 5
#define ENCODER_KEY 0

// User button
#define BOARD_USER_KEY 6
#define BOARD_PWR_EN   15

// WS2812
#define WS2812_NUM_LEDS 8
#define WS2812_DATA_PIN 14

// IR
#define BOARD_IR_EN 2
#define BOARD_IR_RX 1

// SD Card
#define BOARD_SD_CS   13

// CC1101 RF module
#define BOARD_LORA_CS   12
#define BOARD_LORA_IO2  38
#define BOARD_LORA_IO0  3
#define BOARD_LORA_SW1  47
#define BOARD_LORA_SW0  48

// Battery management
#define BOARD_I2C_ADDR_1 0x24  // PN532
#define BOARD_I2C_ADDR_2 0x55  // BQ27220
#define BOARD_I2C_ADDR_3 0x6b  // BQ25896

// NFC
#define BOARD_PN532_RF_REST 45
#define BOARD_PN532_IRQ     17

#endif // PINS_ARDUINO_H
