cmake_minimum_required(VERSION 3.12)

# 前缀变量(方便子文件夹添加文件)
set(DRIVER_PREFIX     "${CMAKE_CURRENT_SOURCE_DIR}/driver")
set(PORTING_PREFIX     "${CMAKE_CURRENT_SOURCE_DIR}/porting")
set(THIRDPARTY_PREFIX  "${CMAKE_CURRENT_SOURCE_DIR}/third_party")

# 资源文件头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/resource/)

# 导入其它CMAKE
include(rules/driver.cmake)
include(rules/pico_sdk_import.cmake)
include(rules/freertos_kernel.cmake)

# 设置C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# 工程名字
project(picoPrj C CXX ASM)

# 初始化PICO SDK
pico_sdk_init()

# 编译参数 -Wno-format -Wno-unused-function -Wno-maybe-uninitialized 是关闭未使用未初始化的函数变量(不推荐)
add_compile_options(-Wall -O2)

# 所有需要编译的源文件
set(SOURCES ${DRIVER_SRC} 
            ${FREERTOS_SRC} 
            main/main.c
    )

# 编译可执行程序
add_executable(${PROJECT_NAME}  ${SOURCES})

# 可执行程序链接PICO库
target_link_libraries(${PROJECT_NAME}   pico_stdlib
                                        hardware_dma
                                        hardware_i2c
                                        hardware_pwm
                                        hardware_spi
                                        hardware_exception
                    )
# 编译其它格式输出
pico_add_extra_outputs(${PROJECT_NAME})

