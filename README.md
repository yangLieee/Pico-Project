# 简介

本项目 硬件基于RP2040 PICO开发板软件基于FreeRTOS系统，关于PICO开发板相关资源可以参考该[中文网站](https://pico.nxez.com/pinout/pico/)，其它使用到的外设将尽可能的进行相应的介绍

# 编译

本工程的代码编译依赖于pico-sdk源码，这部分代码并没有上传可以自行在[github下载](https://github.com/raspberrypi/pico-sdk)，下载后配置好PICO_SDK_PATH环境变量即可按照以下方式进行代码编译

```shell
$ mkdir build
$ cd build
$ cmake ..
```

# LCD-ST7789V

| ST7789V     | PICO               |                |
| ----------- | ------------------ | -------------- |
| 3V3         | 36 - 3V3-OUT       |                |
| GND         | 38 - GND           |                |
| LCD-RST     | 1 - GP0            | 普通IO         |
| LCD-MOSI    | 5 - GP3 - SPI0_TX  | SPI0           |
| LCD-CLK     | 4 - GP2 - SPI0_SCK | SPI0           |
| LCD-CS      | 7 - GP5 - SPI0_CS  | SPI0           |
| LCD-DC      | 6 - GP4            | 普通IO         |
| LCD-BLK     | 2 - GP1            | PWM            |
|             |                    |                |
| TOUCH - SCL | 10 - GP7           | I2C1 - SCL     |
| TOUCH - SDA | 9   - GP6          | I2C1 - SDA     |
| TOUCH - RST | 11 - GP8           | 普通IO         |
| TOUCH - INT | 12 - GP9           | 普通IO（中断） |

需要注意的是这款LCD的控制IC是240x320，而panel是240x280大小

# 运行

编译成功后将有三个编译产物：freertos.elf、freertos.bin和freertos.uf2，其中.uf2格式是USB Flashing Format简写，是一种专门为简化烧录过程设计的格式（由 Microsoft 设计），需把 `.uf2` 文件拖到板子的 USB Mass Storage 设备中即可烧录

| 格式   | 含调试信息 | 直接烧录可用 | 支持 USB 拖放 | 典型用途           |
| ------ | ---------- | ------------ | ------------- | ------------------ |
| `.elf` | ✅ 是       | ❌ 否         | ❌ 否          | 调试、分析符号表   |
| `.bin` | ❌ 否       | ✅ 是         | ❌ 否          | 烧录、加载到 Flash |
| `.uf2` | ❌ 否       | ✅ 是         | ✅ 是          | 拖放烧录           |
