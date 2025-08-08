/**
 * @file dht11.h
 * @brief DHT11温湿度传感器驱动头文件
 */

#ifndef DHT11_H
#define DHT11_H

/**
 * @brief 初始化DHT11传感器
 * @param dht11_gpio 连接的GPIO引脚编号（0-29）
 * @note 此函数会配置指定GPIO引脚并设置初始状态
 *       调用此函数后需要等待至少1秒再进行第一次读取
 */
void dht11_init(uint dht11_gpio);

/**
 * @brief 从DHT11传感器读取温湿度数据
 * @param dht11_gpio 连接的GPIO引脚编号（0-29）
 * @param[out] temperature 用于存储温度值的指针（单位：摄氏度）
 * @param[out] humidity 用于存储湿度值的指针（单位：百分比）
 * @return 0表示成功，-1表示读取失败
 * @note 温度范围：0-50°C (±2°C精度)
 *       湿度范围：20-90% (±5%精度)
 *       两次读取间隔应≥2秒
 *       函数执行时间约4ms（不包含总线通信时间）
 * 
 * @warning 在读取过程中应禁用中断以确保时序准确
 * 
 * 数据格式：
 * [湿度整数(8位), 湿度小数(8位), 
 *  温度整数(8位), 温度小数(8位), 校验和(8位)]
 * 
 * 校验和计算：
 * checksum = (humidity_int + humidity_frac + 
 *             temp_int + temp_frac) & 0xFF
 */
int dht11_read(uint dht11_gpio, float *temperature, float *humidity);

#endif // DHT11_H
