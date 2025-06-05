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
#define ST7789V_WIDTH       240
#define ST7789V_HEIGHT      320
#define ST7789V_SIZE        (ST7789V_WIDTH * ST7789V_HEIGHT)

/* Color Define */
#define RGB565(r, g, b)     (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

#define ST7789V_BLACK       0x0000
#define ST7789V_BLUE        0x001f
#define ST7789V_GREEN       0x07e0
#define ST7789V_RED         0xf800
#define ST7789V_YELLOW      0xffe0
#define ST7789V_WHITE       0xffff
#define ST7789V_ORANGE      0xfd20

/* Struct Param */
typedef struct {
    uint16_t width;
    uint16_t height;
} TFTDevice;

typedef enum {
    ST7789V_DIRECTION_0,
    ST7789V_DIRECTION_90,
    ST7789V_DIRECTION_180,
    ST7789V_DIRECTION_270,
} TFTDirection;


/* Function Interface */

void tftInit(void);

void tftSetWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void tftSetDirection(TFTDirection dir);

void tftClear(uint16_t color);

void tftPlot(uint16_t x, uint16_t y, uint16_t color);

void tftDrawArray(uint16_t* src, size_t len);

void tftSetBlkLight(uint16_t level);



#endif  /* __ST7789V_H__ */

