
# 配置 lvgl根目录 和 配置文件 目录
set(LVGL_ROOT_DIR "${THIRDPARTY_PREFIX}/lvgl-v8.3/")
set(LV_CONF_DIR  "${PORTING_PREFIX}/lvgl-v8.3/")

# LVGL 源文件配置
file(GLOB_RECURSE SOURCES ${LVGL_ROOT_DIR}/src/*.c)

# Benchmark Demo Src
file(GLOB_RECURSE BENCHMARK ${LVGL_ROOT_DIR}/demos/benchmark/assets/*.c)
set(BENCHMARK_SRC   ${BENCHMARK}
                    ${LVGL_ROOT_DIR}/demos/benchmark/lv_demo_benchmark.c)
# Widgets Demo Src
set(WIDGETS_SRC  ${LVGL_ROOT_DIR}/demos/widgets/lv_demo_widgets.c
                 ${LVGL_ROOT_DIR}/demos/widgets/assets/img_demo_widgets_avatar.c
                 ${LVGL_ROOT_DIR}/demos/widgets/assets/img_lvgl_logo.c
                 ${LVGL_ROOT_DIR}/demos/widgets/assets/img_clothes.c)

set(LV_SRC  ${SOURCES}
            ${WIDGETS_SRC}
            ${LV_CONF_DIR}/lv_port_disp.c
            ${LV_CONF_DIR}/lv_port_indev.c)

# 头文件寻找路径
include_directories(${LV_CONF_DIR} ${LVGL_ROOT_DIR})
# 可以直接使用lv_conf.h路径
add_compile_options(-DLV_LVGL_H_INCLUDE_SIMPLE=ON -DLV_CONF_INCLUDE_SIMPLE=ON)
