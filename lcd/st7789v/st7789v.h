#ifndef __ST7789V_H__
#define __ST7789V_H__

#include <stdint.h>

/* SPI Config */
#define LCD_SPI_PORT        spi0
#define LCD_SPI_BAUDRATE    65*1000*1000

/* GPIO Define */
#define LCD_PIN_MOSI        3
#define LCD_PIN_SCK         2
#define LCD_PIN_CS          5
#define LCD_PIN_DC          4
#define LCD_PIN_BLK         1
#define LCD_PIN_RST         0

/* LCD Config */
#define LCD_WIDTH           240
#define LCD_HEIGHT          280
#define LCD_SIZE            (LCD_WIDTH * LCD_HEIGHT)

/* ST7789V IC Config */
#define ST7789V_WIDTH       240
#define ST7789V_HEIGHT      320

/* Register Define */
// 0x36 - Memory Data Access Control
#define MADCTL_MY       (1 << 7)        // Page Address Order ( 0: 定到底; 1: 底到顶)
#define MADCTL_MX       (1 << 6)        // Column Address Order (0: 左到右; 1: 右到左)
#define MADCTL_MV       (1 << 5)        // Page/Column Order (0: 正常; 1: 翻转)
#define MADCTL_ML       (1 << 4)        // Line Address Order (0: 定到底刷新; 1: 底到顶)
#define MADCTL_BGR      (1 << 3)        // MODE (0: RGB; 1: BGR)

/* Register Init List */
const uint8_t register_init_list[] = {
    /* count  cmd     param */ 
     // 1,    0x11,                                     // Turn Off Sleep Mode sleep (delay 120ms)
        3,    0x36,   0x00, 0xA0,                       // Memory Data Access Control (BGR Mode) 
        2,    0x3A,   0x05,                             // Interface Pixel Forma (16bit/pixel)
        6,    0xB2,   0x0C, 0x0C, 0x00, 0x33, 0x33,     // Porch Setting
        2,    0xB7,   0x35,                             // Gate Contro
        2,    0xBB,   0x32,                             // VCOMS Setting (1.35v)
        2,    0xC2,   0x01,                             // VDV and VRH Command Enable 
        2,    0xC3,   0x15,                             // VRH Set (GVDD = 4.8v Color Deep)
        2,    0xC4,   0x20,                             // VDV Set (0v)
        2,    0xC6,   0x0f,                             // Frame Rate Control in Normal Mode (60Hz)
        3,    0xD0,   0xA4, 0xA1,                       // Power Control
        15,   0xE0,   0xD0, 0x08, 0x0E, 0x09, 0x09, 0x05, 0x31, 0x33, 0x48, 0x17, 0x14, 0x15, 0x31, 0x34,   // Positive Voltage Gamma Control
        15,   0xE1,   0xD0, 0x08, 0x0E, 0x09, 0x09, 0x15, 0x31, 0x33, 0x48, 0x17, 0x14, 0x15, 0x31, 0x34,   // Negative Voltage Gamma Control
        1,    0x21,                                     // Display Inversion On 
        1,    0x29,                                     // Display On
        0x00,
};


#endif /* __ST7789V_H__ */

