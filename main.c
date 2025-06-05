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
#include "lcd/st7789v/st7789v.h"

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */
}
/*-----------------------------------------------------------*/

#ifdef JUST_AN_EXAMPLE_ISR

void Dummy_IRQHandler(void)
{
long lHigherPriorityTaskWoken = pdFALSE;

	/* Clear the interrupt if necessary. */
	Dummy_ClearITPendingBit();

	/* This interrupt does nothing more than demonstrate how to synchronise a
	task with an interrupt.  A semaphore is used for this purpose.  Note
	lHigherPriorityTaskWoken is initialised to zero. Only FreeRTOS API functions
	that end in "FromISR" can be called from an ISR. */
	xSemaphoreGiveFromISR( xTestSemaphore, &lHigherPriorityTaskWoken );

	/* If there was a task that was blocked on the semaphore, and giving the
	semaphore caused the task to unblock, and the unblocked task has a priority
	higher than the current Running state task (the task that this interrupt
	interrupted), then lHigherPriorityTaskWoken will have been set to pdTRUE
	internally within xSemaphoreGiveFromISR().  Passing pdTRUE into the
	portEND_SWITCHING_ISR() macro will result in a context switch being pended to
	ensure this interrupt returns directly to the unblocked, higher priority,
	task.  Passing pdFALSE into portEND_SWITCHING_ISR() has no effect. */
	portEND_SWITCHING_ISR( lHigherPriorityTaskWoken );
}
#endif

void thread0(void *priv)
{
	#ifndef PICO_DEFAULT_LED_PIN
	#warning blink example requires a board with a regular LED
	#else
		const uint LED_PIN = PICO_DEFAULT_LED_PIN;
		gpio_init(LED_PIN);
		gpio_set_dir(LED_PIN, GPIO_OUT);
		gpio_put(LED_PIN, 1);
		while (true) {
			gpio_put(LED_PIN, 1);
			vTaskDelay(500);
		}
	#endif
}

void thread1(void *priv)
{
	#ifndef PICO_DEFAULT_LED_PIN
	#warning blink example requires a board with a regular LED
	#else
		const uint LED_PIN = PICO_DEFAULT_LED_PIN;
		gpio_init(LED_PIN);
		gpio_set_dir(LED_PIN, GPIO_OUT);
		gpio_put(LED_PIN, 1);
		while (true) {
			vTaskDelay(250);
			gpio_put(LED_PIN, 0);
			vTaskDelay(250);
		}
	#endif
}

int main() 
{	
    printf("====== %s %s ====== \n",__DATE__,__TIME__);
    stdio_init_all();

#if 0
	/* Create the register test tasks as described at the top of this file.
	These are naked functions that don't use any stack.  A stack still has
	to be allocated to hold the task context. */
	xTaskCreate( 	thread0,			/* Function that implements the task. */
					"thread0",					/* Text name of the task. */
					512,		/* Stack allocated to the task. */
					NULL, 					/* The task parameter is not used. */
					tskIDLE_PRIORITY, 		/* The priority to assign to the task. */
					NULL );					/* Don't receive */

	xTaskCreate( 	thread1,			/* Function that implements the task. */
					"thread1",					/* Text name of the task. */
					512,		/* Stack allocated to the task. */
					NULL, 					/* The task parameter is not used. */
					tskIDLE_PRIORITY+1, 		/* The priority to assign to the task. */
					NULL );					/* Don't receive*/

	/* Start the kernel.  From here on, only tasks and interrupts will run. */
	vTaskStartScheduler();

	for( ;; );
	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then there
	was	insufficient FreeRTOS heap memory available for the idle and/or timer
	tasks to be created.  See the memory management section on the FreeRTOS web
	site, or the FreeRTOS tutorial books for more details. */
#else

    tftInit();

    uint16_t colorList[] = {
        ST7789V_BLUE,
        ST7789V_GREEN,
        ST7789V_RED,      
        ST7789V_YELLOW,      
        ST7789V_WHITE,       
        ST7789V_ORANGE,      
    };

#if 1
    for(int i=0; i<6; i++) {
        tftClear(colorList[i]);
        sleep_ms(3000);
    }
#endif

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

    while(1) {
        sleep_ms(2000);
    }
#endif
	return 0;
}
