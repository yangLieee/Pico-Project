#ifndef __TOUCH_INTERFACE_H__
#define __TOUCH_INTERFACE_H__

#include <stdbool.h>

/**
 * @brief 触摸事件类型枚举
 */
typedef enum {
    TOUCH_NONE,             // 无触摸状态
    TOUCH_UP_GLIDE,         // 向上滑动
    TOUCH_DOWN_GLIDE,       // 向下滑动
    TOUCH_LEFT_GLIDE,       // 向左滑动
    TOUCH_RIGHT_GLIDE,      // 向右滑动
    TOUCH_SINGLE_CLICK,     // 单次点击
    TOUCH_DOUBLE_CLICK,     // 快速双击
    TOUCH_LONG_PRESS,       // 长按
} touch_evt_t;


/**
 * @brief 触摸信息结构体
 */
typedef struct {
    uint16_t x_pos;         // 触摸点X坐标
    uint16_t y_pos;         // 触摸点Y坐标
    touch_evt_t event;      // 触摸事件类型（见touch_evt_t）
} touch_info_t;


/**
 * @brief 触摸中断回调函数类型
 * @param info 触摸事件信息指针
 */
typedef void (*touch_irq_cb)(touch_info_t* info);


/**
 * @brief 触摸屏初始化
 * @param use_irq 是否启用中断模式（true=中断模式，false=轮询模式）
 */
void touch_init(bool use_irq);


/**
 * @brief 获取当前触摸手指数量
 * @return 触摸点数（0=无触摸，1=单点触摸，2=两点触摸）
 */
uint8_t touch_FingerNum(void);


/**
 * @brief 设置触摸中断回调函数
 * @param cb 回调函数指针
 */
void touch_set_irq_callback(touch_irq_cb cb);


/**
 * @brief 获取当前触摸点坐标
 * @param x_pos 存储X坐标的指针（输出参数）
 * @param y_pos 存储Y坐标的指针（输出参数）
 */
void touch_get_xy_axis(uint16_t* x_pos, uint16_t* y_pos);


#endif /* __TOUCH_INTERFACE_H__ */

