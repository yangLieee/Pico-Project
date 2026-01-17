/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "screen_main.h"
#include "screen_menu.h"
#include "screen_menu.h"
#include "screen_menu.h"
#include "screen_setting.h"

static void screen_main_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        screen_main_init();
        break;
    }
    case LV_EVENT_SHORT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_main_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_main (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_main, screen_main_event_handler, LV_EVENT_ALL, ui);
}

static void screen_menu_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        // Init Screen Menu
        screen_menu_init();
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Screen menu Left Code
            screen_menu_update(MOVE_LEFT);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Screen menu Right Code
            screen_menu_update(MOVE_RIGHT);
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_main, guider_ui.screen_main_del, &guider_ui.screen_menu_del, setup_scr_screen_main, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen_menu_img_game_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_game, guider_ui.screen_game_del, &guider_ui.screen_menu_del, setup_scr_screen_game, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_menu_img_setting_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_setting, guider_ui.screen_setting_del, &guider_ui.screen_menu_del, setup_scr_screen_setting, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_menu_img_video_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_video, guider_ui.screen_video_del, &guider_ui.screen_menu_del, setup_scr_screen_video, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_menu_img_music_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_audio, guider_ui.screen_audio_del, &guider_ui.screen_menu_del, setup_scr_screen_audio, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_menu (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_menu, screen_menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_menu_img_game, screen_menu_img_game_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_menu_img_setting, screen_menu_img_setting_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_menu_img_video, screen_menu_img_video_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_menu_img_music, screen_menu_img_music_event_handler, LV_EVENT_ALL, ui);
}

static void screen_game_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_game_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_game (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_game, screen_game_event_handler, LV_EVENT_ALL, ui);
}

static void screen_setting_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        screen_setting_init();
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_game_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_setting (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_setting, screen_setting_event_handler, LV_EVENT_ALL, ui);
}

static void screen_video_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_video_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_video (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_video, screen_video_event_handler, LV_EVENT_ALL, ui);
}

static void screen_audio_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_audio_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_audio (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_audio, screen_audio_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
