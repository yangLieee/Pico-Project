# 简介

本项目 硬件基于RP2040 PICO开发板软件基于FreeRTOS系统，关于PICO开发板相关资源可以参考该[中文网站](https://pico.nxez.com/pinout/pico/)，其它使用到的外设将尽可能的进行相应的介绍

# 下载编译

cmake构建默认可以下载pico-sdk和freertos-kernel，关于自动拉取的功能全部取消掉



FreeRTOS源码编译port.c文件存在编译不通过的问题，新的可以编译文件放于porting/FreeRTOS-Kernel/文件

本工程依赖三方库，但是自行添加cmake规则



![](/home/yanglieee/work/project/pico/myProject/截图 2025-06-21 11-31-01.png)



本工程的代码编译依赖于pico-sdk源码，这部分代码并没有上传可以自行在[github下载](https://github.com/raspberrypi/pico-sdk)，下载后配置好PICO_SDK_PATH环境变量即可按照以下方式进行代码编译

```shell
$ mkdir build
$ cd build
$ cmake ..

cmake -DPICO_STDIO_USB=1  ../
```

# LCD-ST7789V

| ST7789V     | PICO                    |                |
| ----------- | ----------------------- | -------------- |
| 3V3         | 36 - 3V3-OUT            |                |
| GND         | 38 - GND                |                |
| LCD-RST     | 1 - GP0                 | 普通IO         |
| LCD-MOSI    | 5 - GP3 - SPI0_TX       | SPI0           |
| LCD-CLK     | 4 - GP2 - SPI0_SCK      | SPI0           |
| LCD-CS      | 7 - GP5 - SPI0_CS / GND | SPI0           |
| LCD-DC      | 6 - GP4                 | 普通IO         |
| LCD-BLK     | 2 - GP1                 | PWM            |
|             |                         |                |
| TOUCH - SCL | 10 - GP7                | I2C1 - SCL     |
| TOUCH - SDA | 9   - GP6               | I2C1 - SDA     |
| TOUCH - RST | 11 - GP8                | 普通IO         |
| TOUCH - INT | 12 - GP9                | 普通IO（中断） |

关于屏幕的优化：

- 目前SPI-CS管脚直接接地，始终处于片选状态，软件代码方面省掉相应的控制部分
- DMA 16bit传输

需要注意的是这款LCD的控制IC是240x320，而panel是240x280大小

代码实现DC管脚默认是发送数据状态且16比特传输，当发送命令时切换成dc=0，8比特传输

# 运行

编译成功后将有三个编译产物：freertos.elf、freertos.bin和freertos.uf2，其中.uf2格式是USB Flashing Format简写，是一种专门为简化烧录过程设计的格式（由 Microsoft 设计），需把 `.uf2` 文件拖到板子的 USB Mass Storage 设备中即可烧录

| 格式   | 含调试信息 | 直接烧录可用 | 支持 USB 拖放 | 典型用途           |
| ------ | ---------- | ------------ | ------------- | ------------------ |
| `.elf` | ✅ 是       | ❌ 否         | ❌ 否          | 调试、分析符号表   |
| `.bin` | ❌ 否       | ✅ 是         | ❌ 否          | 烧录、加载到 Flash |
| `.uf2` | ❌ 否       | ✅ 是         | ✅ 是          | 拖放烧录           |

# Q&A

1. address_windows 设置是否存在问题，正确设置是否需要减1

2. DMA传输只传输一次就失败？

   初始化后DC=1，DMA传输设置会将DC=0，但是状态没有切回来导致DMA再次传输失败；修改方法即在Send Command之前切成CS=0而命令传输完成立马切成CS=1的状态，这将不会导致问题的出现

3. 



