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
#include "lcd/include/display.h"

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


void thread(void *priv)
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);
    while (true) {
        gpio_put(LED_PIN, 1);
        vTaskDelay(500);
    }
}

int main() 
{	
#if 0
	xTaskCreate( 	thread,			/* Function that implements the task. */
					"thread",					/* Text name of the task. */
					512,		/* Stack allocated to the task. */
					NULL, 					/* The task parameter is not used. */
					tskIDLE_PRIORITY, 		/* The priority to assign to the task. */
					NULL );					/* Don't receive */

	vTaskStartScheduler();
#else

    lcd_dev_t dev = {0};

    stdio_init_all();
    printf("(%s %s) Welcome yangLieee PICO \n", __DATE__, __TIME__);

    lcd_init(&dev);

    uint16_t colorList[] = {
        COLOR_BLUE,
        COLOR_GREEN,
        COLOR_RED,      
        COLOR_YELLOW,      
        COLOR_WHITE,       
        COLOR_ORANGE,      
    };

#if 0
    TFTDirection dir[] = {
        ST7789V_DIRECTION_0,
        ST7789V_DIRECTION_90,
        ST7789V_DIRECTION_180,
        ST7789V_DIRECTION_270,
    };

    for(int i=0; i<4; i++) {
        tftSetDirection(dir[i]);
        tftClear(ST7789V_BLACK);
        tftPlot(30, 50, ST7789V_RED);
        tftPlot(31, 50, ST7789V_RED);

        tftPlot(200, 50, ST7789V_GREEN);
        tftPlot(201, 50, ST7789V_GREEN);

        tftPlot(30, 200, ST7789V_YELLOW);
        tftPlot(31, 201, ST7789V_YELLOW);

        tftPlot(200, 200, ST7789V_WHITE);
        tftPlot(201, 200, ST7789V_WHITE);

        sleep_ms(2000);
    }
#endif
#if 0
    extern TFTDevice dev;

    uint16_t colorful[320], colorIndex = 0;
    tftSetDirection(ST7789V_DIRECTION_90);

    for(int i=0; i<dev.width; i++) {
        if( (i%53 == 0) && (i > 0)) {
            colorIndex++;
        }
        colorful[i] = colorList[colorIndex];
    }

    for(int i=0; i<dev.height; i++) {
        tftDrawArray(colorful, dev.width);
    }

    sleep_ms(1000);

    for(int i=100; i>=0; i-=10) {
        tftSetBlkLight(i);
        sleep_ms(1000);
    }
#endif
#endif

    while(1) {
        for(int i=0; i<6; i++) {
            lcd_clear(colorList[i]);
            sleep_ms(2000);
        }
//        sleep_ms(3000);
    }
	return 0;
}
