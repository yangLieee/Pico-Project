#ifndef __LCDINTERFACE_H__
#define __LCDINTERFACE_H__

#include <stdint.h>
#include <stdbool.h>


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


/**
 * @brief LCD 屏幕旋转方向定义
 */
typedef enum {
    LCD_DIRECTION_0,    // 默认方向（0度旋转，横屏模式）
    LCD_DIRECTION_90,   // 顺时针旋转90度（竖屏模式）
    LCD_DIRECTION_180,  // 旋转180度（倒置横屏）
    LCD_DIRECTION_270,  // 顺时针旋转270度（反向竖屏）
} lcd_dir_t;


/**
 * @brief 图片显示传输模式
 */
typedef enum {
    LCD_CPU_SHOW,           // 使用CPU直接传输
    LCD_DMA_BLOCKING_SHOW,  // 使用DMA阻塞式传输
    LCD_DMA_IRQ_SHOW,       // 使用DMA中断传输
} lcd_show_mode;


/**
 * @brief LCD 设备参数结构体
 */
typedef struct {
    uint32_t width;         // 屏幕物理宽度（像素）
    uint32_t height;        // 屏幕物理高度（像素）
    lcd_dir_t direction;    // 当前显示方向

    uint32_t pwm_slice;     // 背光PWM控制器通道号
    uint32_t dma_channel;   // 保留的DMA通道编号
} lcd_dev_t;


/**
 * @brief LCD 屏幕初始化
 * @note  初始化 LCD 控制器、GPIO、SPI/I2C 接口并重置屏幕，设置为默认显示参数
 */
void lcd_init(void);


/**
 * @brief 设置 LCD 显示方向
 * @param dir 显示方向
 */
void lcd_set_direction(lcd_dir_t dir);


/**
 * @brief 设置 LCD 背光亮度
 * @param level 背光等级（0-100，0 表示关闭，100 表示最大亮度）
 */
void lcd_set_backlight(uint8_t level);


/**
 * @brief 填充矩形区域颜色
 * @param sx 起始 X 坐标
 * @param sy 起始 Y 坐标
 * @param dx 结束 X 坐标
 * @param dy 结束 Y 坐标
 * @param color RGB565 格式颜色
 * @param use_dma 是否使用 DMA 传输
 */
void lcd_fill_color(uint16_t sx, uint16_t sy, uint16_t dx, uint16_t dy, uint16_t color, bool use_dma);


/**
 * @brief 绘制单个像素点
 * @param x X 坐标
 * @param y Y 坐标
 * @param color RGB565 格式颜色
 */
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);


/**
 * @brief 绘制直线
 * @param point1_x 起点 X 坐标
 * @param point1_y 起点 Y 坐标
 * @param point2_x 终点 X 坐标
 * @param point2_y 终点 Y 坐标
 * @param color RGB565 格式颜色
 */
void lcd_draw_line(uint16_t point1_x, uint16_t point1_y, uint16_t point2_x, uint16_t point2_y, uint16_t color);

/**
 * @brief 显示图片
 * @param x 图片左上角 X 坐标
 * @param y 图片左上角 Y 坐标
 * @param w 图片宽度（像素）
 * @param h 图片高度（像素）
 * @param data RGB565 格式像素数组（大小应为 w×h）
 * @param mode 显示模式(CPU/DMA)
 */
void lcd_draw_image(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data, lcd_show_mode mode);


#endif  /* __LCDINTERFACE_H__ */
    
