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
#include "touch/CST816/CST816.h"
#include "lcd/st7789v/lcd_interface.h"

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

void touch_thread(void* priv)
{
    while(true) {
        printf(" %s Loop \n", __func__);
        sleep_ms(1000);
    }
}

void lcd_thread(void* priv)
{
    uint16_t colorList[] = {
        COLOR_BLUE,
        COLOR_GREEN,
        COLOR_RED,      
        COLOR_YELLOW,      
        COLOR_WHITE,       
        COLOR_ORANGE,      
    };
    while(true) {
        printf(" %s Loop \n", __func__);
        sleep_ms(1000);
    }
}

int main() 
{	
    stdio_init_all();
    printf("(%s %s) Welcome yangLieee PICO \n", __DATE__, __TIME__);

    lcd_init();
    CST816_Init();

    xTaskCreate(lcd_thread, "lcd_thread", 512, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(touch_thread, "touch_thread", 512, NULL, tskIDLE_PRIORITY, NULL);
    vTaskStartScheduler();

    while(1) {
        sleep_ms(3000);
    }
    return 0;
}
