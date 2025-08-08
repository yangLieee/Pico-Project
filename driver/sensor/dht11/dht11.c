/**********************************************************
 * Author        : swordslee
 * Email         : jiansong.li@ingenic.com
 * Create date   : 2025-06-17 22:13
 * Last modified : 2025-06-18 09:31
 * Filename      : dht11.c
 * Description   : DHT11 温湿度传感器的驱动
 * *******************************************************/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define DHT11_MAX_TIMINGS 85

// 微秒级延时（使用Pico SDK提供的精确延时）
static inline void delay_us(uint32_t microseconds) {
    busy_wait_us_32(microseconds);
}

// 初始化DHT11传感器
void dht11_init(uint dht11_gpio) {
    gpio_init(dht11_gpio);
    gpio_set_dir(dht11_gpio, GPIO_OUT);
    gpio_put(dht11_gpio, 1); // 初始状态为高电平
}

// 读取DHT11数据
int dht11_read(uint dht11_gpio, float *temperature, float *humidity) {
    int data[5] = {0};
    int counter = 0;
    int j = 0;
    uint8_t checksum = 0;

    // 发送起始信号（拉低1ms，然后拉高20~40us）
    gpio_set_dir(dht11_gpio, GPIO_OUT);
    gpio_put(dht11_gpio, 0);
    delay_us(20 * 1000);  // 20ms
    gpio_put(dht11_gpio, 1);
    delay_us(30);

    // 切换为输入模式，等待DHT11响应
    gpio_set_dir(dht11_gpio, GPIO_IN);

    // 等待DHT11拉低83us
    while (gpio_get(dht11_gpio) == 1) {
        delay_us(1);
        if (++counter > 100) {
            printf("\033[1m\033[31mTimeout waiting for DHT11 to pull low\033[0m\n");
            return -1;
        }
    }

    // 等待DHT11拉高87us
    counter = 0;
    while (gpio_get(dht11_gpio) == 0) {
        delay_us(1);
        if (++counter > 100) {
            printf("\033[1m\033[31mTimeout waiting for DHT11 to pull high\033[0m\n");
            return -1;
        }
    }

    delay_us(87);

    // 读取40bit数据
    for (int i = 0; i < DHT11_MAX_TIMINGS; i++) {
        counter = 0;
        while (gpio_get(dht11_gpio) == 1) { // 等待检测低电平触发
            counter++;
            delay_us(1);
            if (counter > 100) {
                printf("\033[1m\033[35mTimeout waiting for DHT11 to pull low\033[0m\n");
                break;
            }
        }

        while (gpio_get(dht11_gpio) == 0) { // 等待检测高电平触发
            counter++;
            delay_us(1);
            if (counter > 100) {
                printf("\033[1m\033[35mTimeout waiting for DHT11 to pull high\033[0m\n");
                break;
            }
        }

        counter = 0;
        while (gpio_get(dht11_gpio) == 1) { // 检测高电平触发时长
            counter++;
            delay_us(1);
            if (counter > 100) {
                printf("\033[1m\033[31mTimeout waiting for DHT11 to pull high\033[0m\n");
                break;
            }
        }

        data[j / 8] <<= 1;
        if(counter >= 40)
            data[j / 8] |= 1;
        j++;
        if (j >= 40)
            break;      // 已读满40bit则退出
    }

    if (j >= 40) {
        checksum = (data[0] + data[1] + data[2] + data[3]) & 0xFF;
    
        // 允许1位的校验和误差
        if (data[4] == checksum || data[4] == (checksum + 1) || data[4] == (checksum - 1)) {
            *humidity = (float)data[0] + (float)data[1] / 10.0f;    // 湿度 (整数+小数)
            *temperature = (float)data[2] + (float)data[3] / 10.0f; // 温度 (整数+小数)

            // 数据合理性检查
            if (*humidity > 99.9f) *humidity = 99.9f;
            if (*humidity < 0.0f) *humidity = 0.0f;
            if (*temperature > 50.0f) *temperature = 50.0f;
            if (*temperature < 0.0f) *temperature = 0.0f;

            return 0;
        }
        printf("\033[1m\033[31mchecksum error: j=%d, checksum = %d, data=[%02x,%02x,%02x,%02x,%02x]\033[0m\n",
               j, checksum, data[0], data[1], data[2], data[3], data[4]);
        return -1;
    }
    return -1;
}


/*
 *  API
 */ 
void sensor_th_init(uint8_t gpio)
{
    dht11_init(gpio);
}

int sensor_th_read(uint8_t gpio, float* temp, float* humi)
{
    return dht11_read(gpio, temp, humi);
}

