/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen_main;
	bool screen_main_del;
	lv_obj_t *screen_menu;
	bool screen_menu_del;
	lv_obj_t *screen_menu_img_game;
	lv_obj_t *screen_menu_img_setting;
	lv_obj_t *screen_menu_img_video;
	lv_obj_t *screen_menu_img_music;
	lv_obj_t *screen_menu_label_video;
	lv_obj_t *screen_menu_label_game;
	lv_obj_t *screen_menu_label_music;
	lv_obj_t *screen_menu_label_setting;
	lv_obj_t *screen_game;
	bool screen_game_del;
	lv_obj_t *screen_game_spangroup_1;
	lv_span_t *screen_game_spangroup_1_span;
	lv_obj_t *screen_setting;
	bool screen_setting_del;
	lv_obj_t *screen_video;
	bool screen_video_del;
	lv_obj_t *screen_video_spangroup_1;
	lv_span_t *screen_video_spangroup_1_span;
	lv_obj_t *screen_audio;
	bool screen_audio_del;
	lv_obj_t *screen_audio_label_1;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_main(lv_ui *ui);
void setup_scr_screen_menu(lv_ui *ui);
void setup_scr_screen_game(lv_ui *ui);
void setup_scr_screen_setting(lv_ui *ui);
void setup_scr_screen_video(lv_ui *ui);
void setup_scr_screen_audio(lv_ui *ui);
LV_IMG_DECLARE(_Setting_alpha_70x70);
LV_IMG_DECLARE(_Game_alpha_70x70);
LV_IMG_DECLARE(_Video_alpha_70x70);
LV_IMG_DECLARE(_music_alpha_70x70);

LV_FONT_DECLARE(lv_font_Acme_Regular_26)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_Amiko_Regular_12)


#ifdef __cplusplus
}
#endif
#endif
