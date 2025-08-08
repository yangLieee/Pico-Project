#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <stdint.h>

/**
 * @brief 初始化温湿度传感器
 * @param gpio 传感器连接的GPIO引脚号
 * @return 无返回值
 */
void sensor_th_init(uint8_t gpio); 

/**
 * @brief 读取温湿度传感器的当前数据
 * @param temp 指向存储温度值的指针（单位：摄氏度）
 * @param humi 指向存储湿度值的指针（单位：百分比）
 * @return  0表示成功，-1表示读取失败
 */
int sensor_th_read(float* temp, float* humi);




#endif /* __SENSOR_H__ */

