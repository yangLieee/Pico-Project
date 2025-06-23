/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "lvgl.h"

void vApplicationMallocFailedHook( void )
{
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	taskDISABLE_INTERRUPTS();
	for( ;; );
}

void vApplicationTickHook( void )
{
}


bool repeating_timer_callback(__unused struct repeating_timer *t) {
    lv_tick_inc(1);
    return true;
}

/* Reduce Warning */
extern void lv_init(void);
extern void lv_port_disp_init(void);
extern void lv_port_indev_init(void);

int main() 
{	
    stdio_init_all();
    printf("(%s %s) Welcome yangLieee PICO \n", __DATE__, __TIME__);

    struct repeating_timer timer;

    lv_init();                          // LVGL初始化
    lv_port_disp_init();                // 注册LVGL显示任务
    lv_port_indev_init();               // 注册LVGL触屏任务

    add_repeating_timer_ms(1, repeating_timer_callback, NULL, &timer);
    lv_demo_widgets();

    while(1) {
        sleep_ms(5);
        lv_timer_handler();
    }
    return 0;
}
