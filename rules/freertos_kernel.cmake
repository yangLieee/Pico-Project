
# FreeRTOS-Kernel 三方库文件夹路径前缀
set(FREERTOS_PREFIX "${THIRDPARTY_PREFIX}/FreeRTOS-Kernel")

include_directories(${PORTING_PREFIX}/FreeRTOS-Kernel)
include_directories(${FREERTOS_PREFIX}/include)
include_directories(${FREERTOS_PREFIX}/portable/ThirdParty/GCC/RP2040/include/)

set(FREERTOS    croutine.c
                event_groups.c
                list.c
                queue.c
                stream_buffer.c
                tasks.c
                timers.c
                portable/MemMang/heap_4.c
    )

# 目前库中提供的RP2040 port.c函数编译不过, 已将可编译版本移植到porting/FreeRTOS-Kernel/目录下
set(FREERTOS_SRC "${PORTING_PREFIX}/FreeRTOS-Kernel/port.c")        

# 给每个源文件添加前缀
foreach(file ${FREERTOS})
    list(APPEND FREERTOS_SRC "${FREERTOS_PREFIX}/${file}")
endforeach()

