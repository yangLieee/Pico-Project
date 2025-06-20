#ifndef __LCDINTERFACE_H__
#define __LCDINTERFACE_H__

#include <stdint.h>



/* 常用颜色RGB565格式宏定义 */
#define COLOR_WHITE         	 0xFFFF     // 白色
#define COLOR_BLACK         	 0x0000	    // 黑色
#define COLOR_BLUE           	 0x001F     // 蓝色
#define COLOR_GREEN         	 0x07E0     // 绿色
#define COLOR_RED           	 0xF800     // 红色
#define COLOR_YELLOW        	 0xFFE0     // 黄色
#define COLOR_ORANGE             0xFD20     // 橘色

#define COLOR_GRAY  			 0x8430     // 灰色
#define COLOR_BROWN 			 0xBC40     // 棕色
#define COLOR_BRRED 			 0xFC07     // 棕红色
#define COLOR_DARKBLUE      	 0x01CF	    // 深蓝色
#define COLOR_LIGHTBLUE      	 0x7D7C	    // 浅蓝色  
#define COLOR_LIGHTGREEN     	 0x841F     // 浅绿色
#define COLOR_LGRAY 			 0xC618     // 浅灰色(PANNEL) 窗体背景色

#define RGB565(r,g,b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))


/* 旋转角度定义 */
typedef enum {
    LCD_DIRECTION_0,
    LCD_DIRECTION_90,
    LCD_DIRECTION_180,
    LCD_DIRECTION_270,
} lcd_dir_t;

/* 显示图片的模式 */
typedef enum {
    LCD_CPU_SHOW,
    LCD_DMA_BLOCKING_SHOW,
    LCD_DMA_IRQ_SHOW,
} lcd_show_mode;


/* 屏幕参数定义 */
typedef struct {
    uint32_t width;
    uint32_t height;
    lcd_dir_t direction;

    uint32_t pwm_slice;      // BackLight Pwm Channel
    uint32_t dma_channel;    // Data Transfer Dma Channel
} lcd_dev_t;




/* LCD 屏幕初始化 */
void lcd_init(void);

/* LCD 设置方向 */
void lcd_set_direction(lcd_dir_t dir);

/* LCD 设置背光等级<0-100> */
void lcd_set_backlight(uint8_t level);

/* LCD 屏幕填充颜色 */
void lcd_fill_color(uint16_t sx, uint16_t sy, uint16_t dx, uint16_t dy, uint16_t color, bool use_dma);

/* LCD 屏幕某个区域画某个颜色的点 */
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);

/* LCD 屏幕划线 */
void lcd_draw_line(uint16_t point1_x, uint16_t point1_y, uint16_t point2_x, uint16_t point2_y, uint16_t color);

/* LCD屏幕显示图片 */
void lcd_draw_image(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data, lcd_show_mode mode);




#endif  /* __LCDINTERFACE_H__ */
    
