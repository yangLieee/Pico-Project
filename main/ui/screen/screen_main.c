#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lvgl.h"
#include "screen_main.h"

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// 温湿度传感器模拟数据
extern float current_temperature;
extern float current_humidity;

// UI组件
static lv_obj_t *time_label;
static lv_obj_t *date_label;
static lv_obj_t *temp_label;
static lv_obj_t *humidity_label;
static lv_obj_t *temp_arc;
static lv_obj_t *humidity_arc;

// 样式定义
static lv_style_t time_style;
static lv_style_t date_style;
static lv_style_t value_style;
static lv_style_t label_style;
static lv_style_t arc_style;

// 创建UI界面
void screen_main_init(void)
{
    // 初始化样式
    lv_style_init(&time_style);
    lv_style_set_text_font(&time_style, &lv_font_montserrat_14);
    lv_style_set_text_color(&time_style, lv_color_white());

    lv_style_init(&date_style);
    lv_style_set_text_font(&date_style, &lv_font_montserrat_14);
    lv_style_set_text_color(&date_style, lv_color_white());

    lv_style_init(&value_style);
    lv_style_set_text_font(&value_style, &lv_font_montserrat_14);
    lv_style_set_text_color(&value_style, lv_color_white());

    lv_style_init(&label_style);
    lv_style_set_text_font(&label_style, &lv_font_montserrat_14);
    lv_style_set_text_color(&label_style, lv_color_white());

    lv_style_init(&arc_style);
    lv_style_set_arc_color(&arc_style, lv_color_hex(0x4A89DC));
    lv_style_set_arc_width(&arc_style, 8);

    // 创建黑色背景
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_PART_MAIN);

    // 创建时间标签
    time_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(time_label, &time_style, LV_PART_MAIN);
    lv_obj_align(time_label, LV_ALIGN_TOP_MID, 0, 20);
    lv_label_set_text(time_label, "00:00:00");

    // 创建日期标签
    date_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(date_label, &date_style, LV_PART_MAIN);
    lv_obj_align(date_label, LV_ALIGN_TOP_MID, 0, 60);
    lv_label_set_text(date_label, "2025-08-11 Mon");

    // 创建温度弧形指示器
    temp_arc = lv_arc_create(lv_scr_act());
    lv_obj_set_size(temp_arc, 80, 80);
    lv_arc_set_range(temp_arc, 10, 40);
    lv_arc_set_bg_angles(temp_arc, 0, 360);
    lv_arc_set_value(temp_arc, 25);
    lv_obj_remove_style(temp_arc, NULL, LV_PART_KNOB);
    lv_obj_add_style(temp_arc, &arc_style, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(temp_arc, lv_color_hex(0xE9573F), LV_PART_INDICATOR);
    lv_obj_align(temp_arc, LV_ALIGN_BOTTOM_LEFT, 30, -30);

    // 创建温度标签
    lv_obj_t *temp_text = lv_label_create(lv_scr_act());
    lv_obj_add_style(temp_text, &label_style, LV_PART_MAIN);
    lv_label_set_text(temp_text, "Temperature");
    lv_obj_align_to(temp_text, temp_arc, LV_ALIGN_OUT_TOP_MID, 0, -10);

    temp_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(temp_label, &value_style, LV_PART_MAIN);
    lv_label_set_text(temp_label, "25.0°C");
    lv_obj_align_to(temp_label, temp_arc, LV_ALIGN_CENTER, 0, 0);

    // 创建湿度弧形指示器
    humidity_arc = lv_arc_create(lv_scr_act());
    lv_obj_set_size(humidity_arc, 80, 80);
    lv_arc_set_range(humidity_arc, 20, 90);
    lv_arc_set_bg_angles(humidity_arc, 0, 360);
    lv_arc_set_value(humidity_arc, 60);
    lv_obj_remove_style(humidity_arc, NULL, LV_PART_KNOB);
    lv_obj_add_style(humidity_arc, &arc_style, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(humidity_arc, lv_color_hex(0x3BAFDA), LV_PART_INDICATOR);
    lv_obj_align(humidity_arc, LV_ALIGN_BOTTOM_RIGHT, -30, -30);

    // 创建湿度标签
    lv_obj_t *humidity_text = lv_label_create(lv_scr_act());
    lv_obj_add_style(humidity_text, &label_style, LV_PART_MAIN);
    lv_label_set_text(humidity_text, "Humidity");
    lv_obj_align_to(humidity_text, humidity_arc, LV_ALIGN_OUT_TOP_MID, 0, -10);

    humidity_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(humidity_label, &value_style, LV_PART_MAIN);
    lv_label_set_text(humidity_label, "60.0%");
    lv_obj_align_to(humidity_label, humidity_arc, LV_ALIGN_CENTER, 0, 0);

    // 创建分隔线
    lv_obj_t *line = lv_line_create(lv_scr_act());
    static lv_point_t line_points[] = {{0, 100}, {SCREEN_WIDTH, 100}};
    lv_line_set_points(line, line_points, 2);
    lv_obj_set_style_line_width(line, 1, LV_PART_MAIN);
    lv_obj_set_style_line_color(line, lv_color_hex(0x4A4A4A), LV_PART_MAIN);

}
