#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdint.h>

/* Color Define */
#define RGB565(r, g, b)     (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

#define COLOR_BLACK       0x0000
#define COLOR_BLUE        0x001f
#define COLOR_GREEN       0x07e0
#define COLOR_RED         0xf800
#define COLOR_YELLOW      0xffe0
#define COLOR_WHITE       0xffff   
#define COLOR_ORANGE      0xfd20


typedef struct {
    uint32_t width;
    uint32_t height;
} lcd_dev_t;

typedef enum {
    LCD_DIRECTION_0,
    LCD_DIRECTION_90,
    LCD_DIRECTION_180,
    LCD_DIRECTION_270,
} lcd_dir_t;


void lcd_init(lcd_dev_t* dev);

void lcd_set_backlight(uint8_t level);

void lcd_clear(uint16_t color);

void lcd_set_direction(lcd_dev_t* dev, lcd_dir_t dir);


#endif  /* __DISPLAY_H__ */

