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


void setup_scr_screen_menu(lv_ui *ui)
{
    //Write codes screen_menu
    ui->screen_menu = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_menu, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_menu, LV_SCROLLBAR_MODE_ON);

    //Write style for screen_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_menu, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_menu, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_img_game
    ui->screen_menu_img_game = lv_img_create(ui->screen_menu);
    lv_obj_add_flag(ui->screen_menu_img_game, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_menu_img_game, &_Setting_alpha_70x70);
    lv_img_set_pivot(ui->screen_menu_img_game, 50,50);
    lv_img_set_angle(ui->screen_menu_img_game, 0);
    lv_obj_set_pos(ui->screen_menu_img_game, 86, 67);
    lv_obj_set_size(ui->screen_menu_img_game, 70, 70);

    //Write style for screen_menu_img_game, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_menu_img_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_menu_img_game, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_img_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_menu_img_game, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_img_setting
    ui->screen_menu_img_setting = lv_img_create(ui->screen_menu);
    lv_obj_add_flag(ui->screen_menu_img_setting, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_menu_img_setting, &_Game_alpha_70x70);
    lv_img_set_pivot(ui->screen_menu_img_setting, 50,50);
    lv_img_set_angle(ui->screen_menu_img_setting, 0);
    lv_obj_set_pos(ui->screen_menu_img_setting, 242, 67);
    lv_obj_set_size(ui->screen_menu_img_setting, 70, 70);

    //Write style for screen_menu_img_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_menu_img_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_menu_img_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_img_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_menu_img_setting, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_img_video
    ui->screen_menu_img_video = lv_img_create(ui->screen_menu);
    lv_obj_add_flag(ui->screen_menu_img_video, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_menu_img_video, &_Video_alpha_70x70);
    lv_img_set_pivot(ui->screen_menu_img_video, 50,50);
    lv_img_set_angle(ui->screen_menu_img_video, 0);
    lv_obj_set_pos(ui->screen_menu_img_video, 11, 67);
    lv_obj_set_size(ui->screen_menu_img_video, 70, 70);

    //Write style for screen_menu_img_video, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_menu_img_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_menu_img_video, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_img_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_menu_img_video, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_img_music
    ui->screen_menu_img_music = lv_img_create(ui->screen_menu);
    lv_obj_add_flag(ui->screen_menu_img_music, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_menu_img_music, &_music_alpha_70x70);
    lv_img_set_pivot(ui->screen_menu_img_music, 50,50);
    lv_img_set_angle(ui->screen_menu_img_music, 0);
    lv_obj_set_pos(ui->screen_menu_img_music, 160, 67);
    lv_obj_set_size(ui->screen_menu_img_music, 70, 70);

    //Write style for screen_menu_img_music, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_menu_img_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_menu_img_music, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_img_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_menu_img_music, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_label_video
    ui->screen_menu_label_video = lv_label_create(ui->screen_menu);
    lv_label_set_text(ui->screen_menu_label_video, "Video");
    lv_label_set_long_mode(ui->screen_menu_label_video, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_menu_label_video, 0, 157);
    lv_obj_set_size(ui->screen_menu_label_video, 69, 33);

    //Write style for screen_menu_label_video, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_menu_label_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_label_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_menu_label_video, lv_color_hex(0x8a5594), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_menu_label_video, &lv_font_Acme_Regular_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_menu_label_video, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_menu_label_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_menu_label_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_menu_label_video, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_menu_label_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_menu_label_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_menu_label_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_menu_label_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_menu_label_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_menu_label_video, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_label_game
    ui->screen_menu_label_game = lv_label_create(ui->screen_menu);
    lv_label_set_text(ui->screen_menu_label_game, "Game");
    lv_label_set_long_mode(ui->screen_menu_label_game, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_menu_label_game, 86, 157);
    lv_obj_set_size(ui->screen_menu_label_game, 69, 34);

    //Write style for screen_menu_label_game, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_menu_label_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_label_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_menu_label_game, lv_color_hex(0x8a5594), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_menu_label_game, &lv_font_Acme_Regular_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_menu_label_game, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_menu_label_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_menu_label_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_menu_label_game, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_menu_label_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_menu_label_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_menu_label_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_menu_label_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_menu_label_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_menu_label_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_label_music
    ui->screen_menu_label_music = lv_label_create(ui->screen_menu);
    lv_label_set_text(ui->screen_menu_label_music, "Music");
    lv_label_set_long_mode(ui->screen_menu_label_music, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_menu_label_music, 163, 157);
    lv_obj_set_size(ui->screen_menu_label_music, 71, 33);

    //Write style for screen_menu_label_music, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_menu_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_menu_label_music, lv_color_hex(0x8a5594), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_menu_label_music, &lv_font_Acme_Regular_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_menu_label_music, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_menu_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_menu_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_menu_label_music, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_menu_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_menu_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_menu_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_menu_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_menu_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_menu_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_label_setting
    ui->screen_menu_label_setting = lv_label_create(ui->screen_menu);
    lv_label_set_text(ui->screen_menu_label_setting, "Setting");
    lv_label_set_long_mode(ui->screen_menu_label_setting, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_menu_label_setting, 242, 157);
    lv_obj_set_size(ui->screen_menu_label_setting, 80, 33);

    //Write style for screen_menu_label_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_menu_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_menu_label_setting, lv_color_hex(0x8a5594), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_menu_label_setting, &lv_font_Acme_Regular_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_menu_label_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_menu_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_menu_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_menu_label_setting, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_menu_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_menu_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_menu_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_menu_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_menu_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_menu_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_menu.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_menu);

    //Init events for screen.
    events_init_screen_menu(ui);
}
