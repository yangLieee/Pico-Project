/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"


void setup_scr_screen_game(lv_ui *ui)
{
    //Write codes screen_game
    ui->screen_game = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_game, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_game, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_game, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_game_spangroup_1
    ui->screen_game_spangroup_1 = lv_spangroup_create(ui->screen_game);
    lv_spangroup_set_align(ui->screen_game_spangroup_1, LV_TEXT_ALIGN_LEFT);
    lv_spangroup_set_overflow(ui->screen_game_spangroup_1, LV_SPAN_OVERFLOW_CLIP);
    lv_spangroup_set_mode(ui->screen_game_spangroup_1, LV_SPAN_MODE_BREAK);
    //create span
    ui->screen_game_spangroup_1_span = lv_spangroup_new_span(ui->screen_game_spangroup_1);
    lv_span_set_text(ui->screen_game_spangroup_1_span, "GAME");
    lv_style_set_text_color(&ui->screen_game_spangroup_1_span->style, lv_color_hex(0x000000));
    lv_style_set_text_decor(&ui->screen_game_spangroup_1_span->style, LV_TEXT_DECOR_NONE);
    lv_style_set_text_font(&ui->screen_game_spangroup_1_span->style, &lv_font_montserratMedium_12);
    lv_obj_set_pos(ui->screen_game_spangroup_1, 60, 70);
    lv_obj_set_size(ui->screen_game_spangroup_1, 200, 100);

    //Write style state: LV_STATE_DEFAULT for &style_screen_game_spangroup_1_main_main_default
    static lv_style_t style_screen_game_spangroup_1_main_main_default;
    ui_init_style(&style_screen_game_spangroup_1_main_main_default);

    lv_style_set_border_width(&style_screen_game_spangroup_1_main_main_default, 0);
    lv_style_set_radius(&style_screen_game_spangroup_1_main_main_default, 0);
    lv_style_set_bg_opa(&style_screen_game_spangroup_1_main_main_default, 0);
    lv_style_set_pad_top(&style_screen_game_spangroup_1_main_main_default, 0);
    lv_style_set_pad_right(&style_screen_game_spangroup_1_main_main_default, 0);
    lv_style_set_pad_bottom(&style_screen_game_spangroup_1_main_main_default, 0);
    lv_style_set_pad_left(&style_screen_game_spangroup_1_main_main_default, 0);
    lv_style_set_shadow_width(&style_screen_game_spangroup_1_main_main_default, 0);
    lv_obj_add_style(ui->screen_game_spangroup_1, &style_screen_game_spangroup_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_spangroup_refr_mode(ui->screen_game_spangroup_1);

    //The custom code of screen_game.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_game);

    //Init events for screen.
    events_init_screen_game(ui);
}
