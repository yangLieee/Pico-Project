#include "lvgl.h"
#include "gui_guider.h"
#include "screen_menu.h"

#define IMG_CNT             4
#define IMG_CNT_PER_PAGE    3
#define IMG_WIDTH           70
#define IMG_HEIGHT          70
#define EDGE_MARGIN         30      // Left & Right Margin

static uint8_t page_index = 0;
static lv_obj_t * imgs[IMG_CNT];
static lv_obj_t * labels[IMG_CNT];

void screen_menu_init(void)
{
    page_index = 0;
    int target_x = 0;
    int target_y = lv_obj_get_height(guider_ui.screen_menu) / 4;
    int img_gap = (lv_obj_get_width(guider_ui.screen_menu) - 2 * EDGE_MARGIN 
                 - IMG_CNT_PER_PAGE * IMG_WIDTH) / (IMG_CNT_PER_PAGE - 1);

    /* 1. Init Param */
    imgs[0] = guider_ui.screen_menu_img_video;
    imgs[1] = guider_ui.screen_menu_img_game;
    imgs[2] = guider_ui.screen_menu_img_music;
    imgs[3] = guider_ui.screen_menu_img_setting;
    labels[0] = guider_ui.screen_menu_label_video;
    labels[1] = guider_ui.screen_menu_label_game;
    labels[2] = guider_ui.screen_menu_label_music;
    labels[3] = guider_ui.screen_menu_label_setting;

    /* 2. Init Every Icon Location */
    for(uint8_t i = 0; i < IMG_CNT_PER_PAGE; i++) {
        /* Set Size */
        lv_obj_set_size(imgs[i], IMG_WIDTH, IMG_HEIGHT);
        /* Calculate X & Y */
        target_x = EDGE_MARGIN + i * (img_gap + IMG_WIDTH);
        /* Set Init Pos */
        lv_obj_set_pos(imgs[i], target_x, target_y);
        lv_obj_set_pos(labels[i], target_x, lv_obj_get_height(guider_ui.screen_menu) - 80);
    }

    for(uint8_t i = IMG_CNT_PER_PAGE; i < IMG_CNT; i++) {
        /* Set Size */
        lv_obj_set_size(imgs[i], IMG_WIDTH, IMG_HEIGHT);
        /* Hide Image */
        lv_obj_add_flag(imgs[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(labels[i], LV_OBJ_FLAG_HIDDEN);
    }
}

void screen_menu_update(move_dir_t dir)
{
    /* Branch */
    if(dir == MOVE_LEFT && page_index == 0) {
        page_index = 1;
    } else if(dir == MOVE_RIGHT && page_index == 1) {
        page_index = 0;
    } else {
        return;
    }

    /* Calculate Param */
    int target_x;
    int target_y = lv_obj_get_height(guider_ui.screen_menu) / 4;
    int img_gap = (lv_obj_get_width(guider_ui.screen_menu) - 2 * EDGE_MARGIN 
                 - IMG_CNT_PER_PAGE * IMG_WIDTH) / (IMG_CNT_PER_PAGE - 1);
    int cnt = (page_index + 1) * IMG_CNT_PER_PAGE > IMG_CNT ? IMG_CNT : (page_index + 1) * IMG_CNT_PER_PAGE;

    /* Hide Forward Page */
    for(uint8_t i = 0; i < page_index * IMG_CNT_PER_PAGE; i++) {
        lv_obj_add_flag(imgs[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(labels[i], LV_OBJ_FLAG_HIDDEN);
    }

    /* Display Page */
    for(uint8_t i = page_index * IMG_CNT_PER_PAGE, j = 0; i < cnt; i++, j++) {
        /* Calculate X & Y */
        target_x = EDGE_MARGIN + j * (img_gap + IMG_WIDTH);
        /* Set Init Pos */
        lv_obj_set_pos(imgs[i], target_x, target_y);
        lv_obj_set_pos(labels[i], target_x, lv_obj_get_height(guider_ui.screen_menu) - 80);
        /* Clear Hide */
        lv_obj_clear_flag(imgs[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(labels[i], LV_OBJ_FLAG_HIDDEN);
    }

    /* Hide Afterward */
    for(uint8_t i = (page_index + 1) * IMG_CNT_PER_PAGE, j = 0; i < IMG_CNT; i++, j++) {
        lv_obj_add_flag(imgs[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(labels[i], LV_OBJ_FLAG_HIDDEN);
    }
}


void screen_img_zoom(void)
{
#if 0
    /* 缩放动画变换 */
    ui_animation(imgs[i],       // Image Obj
            AniTime,       // Duration
            0,             // Delay     
            lv_img_get_zoom(guider_ui.screen_menu_img_video),  // 动画开始的起始值 获取缩放系数
            ImgZoom,                                           // 动画开始的结束值
            &lv_anim_path_linear,                              // 动画曲线的回调（线性变化/淡入/淡出）
            0,             // Repeat count 
            0,             // Repeat Delay
            0,             // Playback Time
            0,             // Playback Delay 
            (lv_anim_exec_xcb_t)lv_img_set_zoom,               // 动画效果的回调函数
            NULL,          // Start Callback
            NULL,          // Ready Callback 
            NULL);         // Delete Callback

    /* 坐标动画变换 */
    int target_x = (lv_obj_get_width(guider_ui.screen_menu) / 2) + (zoom_img_width / 2 ) + IMG_GAP;
    ui_animation(imgs[i], 
            AniTime,
            0, 
            lv_obj_get_x(imgs[i]),
            target_x,
            &lv_anim_path_linear,
            0, 0, 0, 0,
            (lv_anim_exec_xcb_t)lv_obj_set_x,
            NULL, NULL, NULL);
#endif
}
