/**
 * @file lv_port_disp_templ.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>
#include <stddef.h>
#include "../driver/interface/lcd_interface.h"

/*********************
 *      DEFINES
 *********************/
#ifndef MY_DISP_HOR_RES
    #define MY_DISP_HOR_RES    240
#endif

#ifndef MY_DISP_VER_RES
    #define MY_DISP_VER_RES    280
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
//static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//        const lv_area_t * fill_area, lv_color_t color);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/
#if(PLATFORM_RP2350)
    #define BUFFER_SIZE     (MY_DISP_HOR_RES * MY_DISP_VER_RES)
#elif(PLATFORM_RP2040)
    #define BUFFER_SIZE     (MY_DISP_HOR_RES * 100)
#endif

    static lv_disp_draw_buf_t draw_buf_dsc;
    static lv_color_t buf_1[BUFFER_SIZE];
    static lv_color_t buf_2[BUFFER_SIZE];
    lv_disp_draw_buf_init(&draw_buf_dsc, buf_1, buf_2, BUFFER_SIZE);

    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/

    static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc;

#if(PLATFORM_RP2350)
    /* BUG TODO */
    /* disp_drv.full_refresh = 1; */
#endif

    disp_drv.sw_rotate = 1;   			 // add for rotation
    disp_drv.rotated = LV_DISP_ROT_270;  // add for rotation

    /* Fill a memory array with a color if you have GPU.
     * Note that, in lv_conf.h you can enable GPUs that has built-in support in LVGL.
     * But if you have a different GPU you can use with this callback.*/
    //disp_drv.gpu_fill_cb = gpu_fill;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    lcd_init();
    /* lcd_set_direction(LCD_DIRECTION_90); */
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    if(disp_flush_enabled) {
        /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/

#if 0
        int32_t x;
        int32_t y;
        for(y = area->y1; y <= area->y2; y++) {
            for(x = area->x1; x <= area->x2; x++) {
                lcd_draw_point(x, y, color_p->full);
                color_p++;
            }
        }
#else
        lcd_draw_image(area->x1, area->y1, area->x2 - area->x1 +1, area->y2 - area->y1 +1, &color_p->full, LCD_DMA_BLOCKING_SHOW);
#endif
    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

