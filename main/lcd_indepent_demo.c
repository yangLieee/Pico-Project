#include <stdio.h>
#include "lcd_interface.h"
#include "touch_interface.h"
#include "image/xiaoxin_w200_h180_rgb565.h"

static void touch_irq_callback(touch_info_t* info)
{
    printf("X-Y (%d, %d) Event %d \n", info->x_pos, info->y_pos, info->event);
}

void lcd_driver_demo(void)
{
    lcd_init();
    touch_init(true);
    touch_set_irq_callback(touch_set_irq_callback);

    uint16_t colorList[] = {
        COLOR_BLUE,
        COLOR_GREEN,
        COLOR_RED,      
        COLOR_YELLOW,      
        COLOR_ORANGE,      
        COLOR_BRRED,
        COLOR_DARKBLUE,
        COLOR_LIGHTBLUE,
        COLOR_LGRAY,
        COLOR_WHITE,       
    };

    while(true) {
        /* 1. BackLight Test */
        printf("********** BACKLIGHT TEST **********\n");
        lcd_fill_color(0, 0, 240, 320, COLOR_WHITE, 1);
        for(int i=0; i<100; i+=10) {
            lcd_set_backlight(i);
            sleep_ms(2000);
        }
        /* 2. Cpu Color Test */
        printf("********** CPU COLOR FILL TEST **********\n");
        for(int i=0; i<10; i++) {
            lcd_fill_color(0, 0, 200, 200, colorList[i], 0);
            sleep_ms(2000);
        }
        /* 3. DMA Color Test */ 
        printf("********** DMA COLOR FILL TEST **********\n");
        for(int i=0; i<10; i++) {
            lcd_fill_color(10, 10, 210, 210, colorList[i], 1);
            sleep_ms(2000);
        }
        /* 4. Draw Point Test */  
        printf("********** DRAW POINT TEST **********\n");
        for(int i=20; i < 100; i+=5) {
            for(int j=100; j < 200; j+=5) {
                lcd_draw_point(i, j, colorList[i%10]);
                sleep_ms(10);
            }
        }
        /* 5. Draw Line Test */  
        printf("********** DRAW LINE TEST **********\n");
        for(int m = 120, n = 160, i = 0; m < 200; m += 10, n += 10, i++) {
            lcd_draw_line(m, 120, n, 160, colorList[i]);
            sleep_ms(100);
        }
        /* 6. Draw Pictures Test */
        printf("********** DRAW PICTURE & ROTATE TEST **********\n");
        for(int i=3; i>=0; i--) {
            lcd_set_direction((lcd_dir_t)i);
            lcd_draw_image(0, 0, 200, 180, image_data, LCD_CPU_SHOW);
            sleep_ms(2000);
        }
    }
}
