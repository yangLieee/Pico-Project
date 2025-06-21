#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"
#include "hardware/dma.h"
#include "pico/stdlib.h"
#include "st7789v.h"
#include "lcd_interface.h"

static lcd_dev_t dev;

static inline void st7789v_set_dc(bool dc)
{
    gpio_put_masked( (1 << LCD_PIN_DC) , (dc << LCD_PIN_DC));
}

static inline void st7789v_write_cmd(const uint8_t *cmd, size_t len)
{
    spi_set_format(LCD_SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    st7789v_set_dc(0);
    spi_write_blocking(LCD_SPI_PORT, cmd, 1);               // Send CMD
    st7789v_set_dc(1);
    if(len > 1) 
        spi_write_blocking(LCD_SPI_PORT, &cmd[1], len-1);   // CMD With Data
    spi_set_format(LCD_SPI_PORT, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
}

static inline void st7789v_write16_data(const uint16_t data)
{
    spi_write16_blocking(LCD_SPI_PORT, &data, 1);
}

static inline void st7789v_set_address_windows(uint16_t sx, uint16_t sy, uint16_t dx, uint16_t dy)
{
    uint8_t cmd = 0;
    uint16_t x1=0, x2=0, y1=0, y2=0;
	if (dev.direction == LCD_DIRECTION_0 || dev.direction == LCD_DIRECTION_180) {
        x1 = sx;
        x2 = dx;
        y1 = sy + 20;
        y2 = dy + 20;
	} else if (dev.direction == LCD_DIRECTION_90 || dev.direction == LCD_DIRECTION_270) {
        x1 = sx + 20;
        x2 = dx + 20;
        y1 = sy;
        y2 = dy;
    }

    cmd = 0x2a;
    st7789v_write_cmd(&cmd, 1);
    st7789v_write16_data(x1);
    st7789v_write16_data(x2);

    cmd = 0x2b;
    st7789v_write_cmd(&cmd, 1);
    st7789v_write16_data(y1);
    st7789v_write16_data(y2);

    cmd = 0x2c;
    st7789v_write_cmd(&cmd, 1);
}

static inline void st7789v_set_dir(lcd_dir_t dir)
{
    uint8_t temp = 0;
    switch(dir) {
        case LCD_DIRECTION_0:
            break;
        case LCD_DIRECTION_90:
            temp =  MADCTL_MX | MADCTL_MV;  // 0x60
            break;
        case LCD_DIRECTION_180:
            temp =  MADCTL_MY | MADCTL_MX;  // 0xC0
            break;
        case LCD_DIRECTION_270:
            temp = MADCTL_MY | MADCTL_MV;   // 0xA0 
            break;
        default:
            break;
    }

    uint8_t cmd[2] = {0x36, temp};
    st7789v_write_cmd(cmd, 2);

    dev.direction = dir;
    st7789v_set_address_windows(0, 0, dev.width-1, dev.height-1);
}

static inline uint32_t st7789v_pin_init(void)
{
    gpio_init(LCD_PIN_DC);
    gpio_init(LCD_PIN_RST);

    gpio_set_function(LCD_PIN_BLK,  GPIO_FUNC_PWM);
    gpio_set_function(LCD_PIN_CS,   GPIO_FUNC_SPI);
    gpio_set_function(LCD_PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(LCD_PIN_MOSI, GPIO_FUNC_SPI);

    gpio_set_dir(LCD_PIN_DC,  true);
    gpio_set_dir(LCD_PIN_RST, true);

    return spi_init(LCD_SPI_PORT, LCD_SPI_BAUDRATE);
}

static inline void st7789v_reset(void)
{
    gpio_put(LCD_PIN_RST, false);
    sleep_ms(100);
    gpio_put(LCD_PIN_RST, true);
    sleep_ms(100);
}

static void spi_dma_handler(void)
{
    if(dma_channel_get_irq0_status(dev.dma_channel)) {
        dma_channel_acknowledge_irq0(dev.dma_channel);
    }
}

static inline void st7789v_dma_init(void)
{
    uint32_t dma_chn = dma_claim_unused_channel(true);
    dma_channel_config c = dma_channel_get_default_config(dma_chn);
    channel_config_set_dreq(&c, spi_get_dreq(LCD_SPI_PORT, true));
    channel_config_set_transfer_data_size(&c, DMA_SIZE_16);
    channel_config_set_read_increment(&c, false);
    dma_channel_configure(dma_chn, &c, &spi_get_hw(LCD_SPI_PORT)->dr, NULL, 0, false);

    dma_channel_set_irq0_enabled(dma_chn, true);
    irq_set_exclusive_handler(DMA_IRQ_0, spi_dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);

    dev.dma_channel = dma_chn;
}

static inline void st7789v_blk_init(void)
{
    /* freq_pwm = f_sys / period = fsys / ((TOP + 1) + DIV) */
    uint32_t blkPwmSlice = 0;
    blkPwmSlice = pwm_gpio_to_slice_num(LCD_PIN_BLK);
    pwm_set_clkdiv(blkPwmSlice, 50.0f);     // Set DIV (125M / 50 = 25kHz)
    pwm_set_wrap(blkPwmSlice, 99);          // Set TOP
    pwm_set_chan_level(blkPwmSlice, PWM_CHAN_B, 100);
    pwm_set_enabled(blkPwmSlice, true);

    dev.pwm_slice = blkPwmSlice;
}

static inline void st7789v_register_init(const uint8_t* cmd) 
{
    uint32_t count = 0;
    uint8_t reg = 0x11;
    st7789v_write_cmd(&reg, 1);
    sleep_ms(120);
    do {
        count = cmd[0];
        st7789v_write_cmd(&cmd[1], count);
        cmd += (count + 1);
    } while(cmd[0]);
}


static inline void st7789v_set_blk(uint16_t level)
{
    if(level > 0 || level < 100) {
        pwm_set_chan_level(dev.pwm_slice, PWM_CHAN_B, level);
    }
}

static inline void st7789v_dma_clear(const uint16_t* data, uint32_t size)
{
    uint32_t chn = dev.dma_channel;
    dma_channel_config c = dma_get_channel_config(chn);
    channel_config_set_read_increment(&c, true);
    dma_channel_set_config(chn, &c, false);
    dma_channel_transfer_from_buffer_now(chn, data, size);
}

static inline void st7789v_dma_clear_blocking(const uint16_t color, uint32_t size)
{
    uint32_t chn = dev.dma_channel;
    dma_channel_config c = dma_get_channel_config(chn);
    channel_config_set_read_increment(&c, false);
    dma_channel_set_config(chn, &c, false);
    dma_channel_transfer_from_buffer_now(dev.dma_channel, &color, size);
    dma_channel_wait_for_finish_blocking(dev.dma_channel);
}

static inline void st7789v_cpu_clear(uint16_t color, uint32_t size)
{
    for(size_t i=0; i < size; i++) {
        st7789v_write16_data(color);
    }
}


/*
 * LCD Interface
 */

void lcd_init()
{
    /* 1. GPIO Init */
    uint32_t baudrate = st7789v_pin_init();
    /* 2. DMA Init */
    st7789v_dma_init();
    /* 3. Reset LCD */
    st7789v_reset();
    /* 4. Init Register List */
    st7789v_register_init(register_init_list);
    /* 5. Set Default Direction */
    st7789v_set_dir(LCD_DIRECTION_0);
    /* 6. Set Default Color */
    st7789v_cpu_clear(COLOR_WHITE, LCD_SIZE);
    /* 7. BackLight Init */
    st7789v_blk_init();
    spi_set_format(LCD_SPI_PORT, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    printf("TFT LCD <ST7789V> Init Ok baudrate [%ld] \n", baudrate);
}

void lcd_set_direction(lcd_dir_t dir)
{
    st7789v_set_dir(dir);
}

void lcd_set_backlight(uint8_t level)
{
    st7789v_set_blk(level);
}

void lcd_fill_color(uint16_t sx, uint16_t sy, uint16_t dx, uint16_t dy, uint16_t color, bool use_dma)
{
    int size = (dx - sx + 1) * (dy - sy + 1);
    st7789v_set_address_windows(sx, sy, dx, dy);
    if(use_dma)
        st7789v_dma_clear_blocking(color, size);
    else
        st7789v_cpu_clear(color, size);
}

void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    st7789v_set_address_windows(x, y, x, y);
    st7789v_write16_data(color);
}

void lcd_draw_line(uint16_t point1_x, uint16_t point1_y, uint16_t point2_x, uint16_t point2_y, uint16_t color)
{
    uint16_t sx = point1_x;
    uint16_t sy = point1_y;
    int delta_x, delta_y, step_x, step_y, err_x=0, err_y=0, distance; // 增量 和 单步方向

    delta_x = point2_x - point1_x;
    delta_y = point2_y - point1_y;

    if(delta_x > 0) 
        step_x = 1;
    else if(delta_x == 0) 
        step_x = 0;
    else {
        step_x = -1;
        delta_x = -delta_x;
    }
    
    if(delta_y > 0) 
        step_y = 1;
    else if(delta_y == 0) 
        step_y = 0;
    else {
        step_y = -1;
        delta_y = -delta_y;
    }

    distance = (delta_x > delta_y) ? delta_x : delta_y; //选取基本增量坐标轴

    for(int i=0; i < distance + 1; i++) {
        lcd_draw_point(sx, sy, color);

        err_x += delta_x;
        err_y += delta_y;
        if(err_x > distance) {
            err_x -= distance;
            sx += step_x;
        }
        if(err_y > distance) {
            err_y -= distance;
            sy += step_y;
        }
    }
}

void lcd_draw_image(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data, lcd_show_mode mode)
{
    if ((x >= ST7789V_WIDTH) || (y >= ST7789V_HEIGHT))
        return;
    if ((x + w - 1) >= ST7789V_WIDTH)
        return;
    if ((y + h - 1) >= ST7789V_HEIGHT)
        return;

    st7789v_set_address_windows(x, y, x + w-1, y + h-1);
    if(mode == LCD_CPU_SHOW) {
        for(size_t i=0; i < w*h; i++) {
            st7789v_write16_data(data[i]);
        }
    }
    else if(mode == LCD_DMA_BLOCKING_SHOW) {
        for(size_t i=0; i < w*h; i++) {
            st7789v_dma_clear_blocking(data[i], 1);
        }
    }
    else{
        st7789v_dma_clear(data, w*h);
    }

}



