# 简介

本项目 硬件基于RP2040 PICO开发板软件基于FreeRTOS系统，关于PICO开发板相关资源可以参考该[中文网站](https://pico.nxez.com/pinout/pico/)，目前已经实现屏幕的显示以及触摸功能。代码目录结构如下

```shell
.
├── CMakeLists.txt			# 顶层编译规则
├── docs					# 文档目录
├── driver					# 驱动目录
│   ├── interface				# 接口
│   ├── lcd						# LCD显示驱动
│   └── touch					# 触摸驱动
├── main					# 应用及示例
│   └── main.c					# 主函数
├── porting					# 移植目录(针对三方库的配置或改动)
├── resource				# 资源文件
│   ├── audio					# 音频 
│   ├── image					# 图片
│   └── video					# 视频
├── rules					# 子模块编译规则
└── third_party				# 三方库存储目录
    ├── FreeRTOS-Kernel			# FreeRTOS-Kernel
    └── pico-sdk				# Pico-SDK

```

# 功能

1. 支持 RP2040 和 RP2350 两个平台

   通过rules/option.cmake配置选项进行配置即可

2. 支持USB作串口DEBUG（默认打开）

3. 支持LVGL

4. 支持PWM AUDIO

# 下载及编译

1. 下载

   代码结构采用submodule的形式，单独clone只能下载主工程，如果网络较慢当执行submodule init时，可能存在拉取不下来的情况，此时可以直接下载zip文件替换到对应位置即可。同样对于pico-sdk//lib/中的submodule也可以采取同样的方法

   ```shell
   # 下载仓库
   $ git clone https://github.com/yangLieee/Pico-Project.git
   
   # 切换分支
   $ git checkout release
   
   # 初始化所有子模块，并根据当前提交指向的版本将内容拉下来(FreeRTOS & Pico-SDK)
   $ git submodule update --init
   
   # 递归处理子模块里的子模块, Pico-SDK/lib/目录下存储的
   $ git submodule update --init --recursive
   ```

2. 编译

   ```shell
   $ mkdir build
   # 默认USB作串口DEBUG
   $ cmake ..
   $ make 
   ```

# 运行

编译成功后将有三个编译产物：freertos.elf、freertos.bin和freertos.uf2，其中.uf2格式是USB Flashing Format简写，是一种专门为简化烧录过程设计的格式（由 Microsoft 设计），需把 `.uf2` 文件拖到板子的 USB Mass Storage 设备中即可烧录

| 格式   | 含调试信息 | 直接烧录可用 | 支持 USB 拖放 | 典型用途           |
| ------ | ---------- | ------------ | ------------- | ------------------ |
| `.elf` | ✅ 是       | ❌ 否         | ❌ 否          | 调试、分析符号表   |
| `.bin` | ❌ 否       | ✅ 是         | ❌ 否          | 烧录、加载到 Flash |
| `.uf2` | ❌ 否       | ✅ 是         | ✅ 是          | 拖放烧录           |

# 外设介绍

## LCD-ST7789V

| ST7789V  | PICO                    |        |
| -------- | ----------------------- | ------ |
| 3V3      | 36 - 3V3-OUT            |        |
| GND      | 38 - GND                |        |
| LCD-RST  | 1 - GP0                 | 普通IO |
| LCD-MOSI | 5 - GP3 - SPI0_TX       | SPI0   |
| LCD-CLK  | 4 - GP2 - SPI0_SCK      | SPI0   |
| LCD-CS   | 7 - GP5 - SPI0_CS / GND | SPI0   |
| LCD-DC   | 6 - GP4                 | 普通IO |
| LCD-BLK  | 2 - GP1                 | PWM    |

该屏幕IC FrameBuffer 240x320，但是panel大小240x280，在对于起始终止坐标的设置需要特别注意，另外在该工程中对于屏幕显示有两个部分优化：

- 目前SPI-CS管脚直接接地，始终处于片选状态，软件代码方面省掉相应的控制部分
- DMA 16bit传输

## TOUCH-CST816

触摸部分的供电复用LCD部分

| ST7789V     | PICO      |                |
| ----------- | --------- | -------------- |
| TOUCH - SCL | 10 - GP7  | I2C1 - SCL     |
| TOUCH - SDA | 9   - GP6 | I2C1 - SDA     |
| TOUCH - RST | 11 - GP8  | 普通IO         |
| TOUCH - INT | 12 - GP9  | 普通IO（中断） |

# 其它说明

1. 如果直接使用FreeRTOS源码的port.c文件编译将出现sio定义的错误，针对该问题将默认文件改动移植到porting/FreeRTOS-Kernel/文件下

# Q&A

1. 设置整个屏幕的显示，但是存在白边?

   坐标设置和宽高设置是不一样的，坐标设置是从(0,0)开始，而宽高是一个数值从1计数，所以需要实际的尺寸-1才是实际的坐标位置

2. DMA模式只传输一次就失败?

   初始化后DC=1，DMA传输设置会将DC=0，但是状态没有切回来导致DMA再次传输失败；修改方法即在Send Command之前切成CS=0 8bit传输而命令传输完成立马切成CS=1 16bit传输的状态，这将不会导致问题的出现

3. 在CMakeLists中add_compile_options添加 -DPICO_STDIO_USB=1 不生效？
   生效的时间比较晚，通常在pico_sdk_init()阶段已经读取配置成功，只能在这个函数执行之前通过set或者option进行设置

# TODO

1. lvgl屏幕适配文件驱动 full_refresh=1 出错
