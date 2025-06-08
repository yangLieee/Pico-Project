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

#define ST7789V_WIDTH       240
#define ST7789V_HEIGHT      320
#define ST7789V_SIZE        (ST7789V_WIDTH * ST7789V_HEIGHT)


/*
 * ST7789V的支持得到最大分辨率为240*320，该显示屏支持240*280，故有偏移量
 * 偏移量计算举例：（320-280）/ 2 = 20
 */
#define WIDTH_OFFSET        (ST7789V_WIDTH - LCD_WIDTH) / 2 
#define HEIGHT_OFFSET       (ST7789V_HEIGHT - LCD_HEIGHT) / 2 

//void tftSetWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
//
//void tftPlot(uint16_t x, uint16_t y, uint16_t color);
//
//void tftDrawArray(uint16_t* src, size_t len);

#endif  /* __ST7789V_H__ */

