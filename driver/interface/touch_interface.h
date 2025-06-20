#ifndef __TOUCH_INTERFACE_H__
#define __TOUCH_INTERFACE_H__

typedef enum {
    TOUCH_NONE,             // 无操作
    TOUCH_UP_GLIDE,         // 上划
    TOUCH_DOWN_GLIDE,       // 下划
    TOUCH_LEFT_GLIDE,       // 左划
    TOUCH_RIGHT_GLIDE,      // 右划
    TOUCH_SINGLE_CLICK,     // 单击
    TOUCH_DOUBLE_CLICK,     // 双击
    TOUCH_LONG_PRESS,       // 长按
} touch_evt_t;

typedef struct {
    uint16_t x_pos;         // X坐标
    uint16_t y_pos;         // Y坐标
    touch_evt_t event;      // 触摸事件
} touch_info_t;


typedef void (*touch_irq_cb)(touch_info_t* info);


/* 触摸屏的初始化函数 */
void touch_init(void);

/* 设置中断回调函数 */
void touch_set_irq_callback(touch_irq_cb cb);

/* 获取XY坐标 */
void touch_get_xy_axis(uint16_t* x_pos, uint16_t* y_pos);



#endif /* __TOUCH_INTERFACE_H__ */

