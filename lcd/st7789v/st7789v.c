#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"
#include "hardware/dma.h"
#include "pico/stdlib.h"
#include "st7789v_reg.h"
#include "st7789v.h"
#include "display.h"

static uint8_t blkPwmSlice;

static volatile bool clearInProcess = false;
static uint16_t dmaClearTx;

static inline void st7789v_set_dc(bool dc)
{
    gpio_put_masked( (1 << LCD_PIN_DC) , (dc << LCD_PIN_DC));
}

static inline void st7789v_write_cmd(const uint8_t *cmd, size_t len)
{
    st7789v_set_dc(0);
    spi_write_blocking(LCD_SPI_PORT, cmd, 1);

    // With Param
    if(len > 1) {
        st7789v_set_dc(1);
        spi_write_blocking(LCD_SPI_PORT, &cmd[1], len-1);
    }
}

static inline void st7789v_write_data8(const uint16_t data)
{
    uint8_t array[2];
    st7789v_set_dc(1);
    array[0] = (data >> 8) & 0xff;
    array[1] = (data & 0xff);
    spi_write_blocking(LCD_SPI_PORT, array, 2);
}

static inline void st7789v_write_data16(const uint16_t data)
{
    st7789v_set_dc(1);
    spi_write16_blocking(LCD_SPI_PORT, &data, 1);
}

static inline void st7789v_set_windows(lcd_dev_t* dev, uint16_t sx, uint16_t sy, uint16_t dx, uint16_t dy)
{
    uint8_t cmd = 0;

    cmd = 0x2a;
    st7789v_write_cmd(&cmd, 1);
    st7789v_write_data8(sx + WIDTH_OFFSET);
    st7789v_write_data8(dx + WIDTH_OFFSET);

    cmd = 0x2b;
    st7789v_write_cmd(&cmd, 1);
    st7789v_write_data8(sy + HEIGHT_OFFSET);
    st7789v_write_data8(dy + HEIGHT_OFFSET);

    cmd = 0x2c;
    st7789v_write_cmd(&cmd, 1);
}

#if 0
void tftPlot(uint16_t x, uint16_t y, uint16_t color)
{
    tftSetWindow(x, y, 1, 1);
    st7789v_write_data16(color);
}

void tftDrawArray(uint16_t* src, size_t len)
{
    for(size_t i=0; i < len; i++) {
        st7789v_write_data16(src[i]);
    }
}
#endif

static inline void st7789v_set_blk(uint16_t level)
{
    if(level > 0 || level < 100) {
        pwm_set_chan_level(blkPwmSlice, PWM_CHAN_B, level);
    }
}

static inline void st7789v_clear_fullscreen (uint16_t color)
{
    size_t fillsize = ST7789V_SIZE;
    for(size_t i=0; i < fillsize; i++) {
        st7789v_write_data16(color);
    }
}
static inline void st7789v_set_dir(lcd_dev_t* dev, lcd_dir_t dir)
{
    uint8_t temp = 0;
    switch(dir) {
        case LCD_DIRECTION_0:
            dev->width  = LCD_WIDTH;
            dev->height = LCD_HEIGHT;
            temp =  MADCTL_MX;
            break;
        case LCD_DIRECTION_90:
            dev->width  = LCD_WIDTH;
            dev->height = LCD_HEIGHT;
            temp =  MADCTL_MV;
            break;
        case LCD_DIRECTION_180:
            dev->width  = LCD_WIDTH;
            dev->height = LCD_HEIGHT;
            temp =  MADCTL_MY;
            break;
        case LCD_DIRECTION_270:
            dev->width  = LCD_WIDTH;
            dev->height = LCD_HEIGHT;
            temp =  MADCTL_MX | MADCTL_MY | MADCTL_MV;
            break;
        default:
            break;
    }

    uint8_t cmd[2] = {0x36, temp};
    st7789v_write_cmd(cmd, 2);

    st7789v_set_windows(dev, 0, 0, dev->width, dev->height);
}

static inline void st7789v_reset(void)
{
    gpio_put(LCD_PIN_RST, false);
    sleep_ms(100);
    gpio_put(LCD_PIN_RST, true);
    sleep_ms(100);
}


static inline int st7789v_pin_init(void)
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


static void clearComplete(void)
{
    if(dma_channel_get_irq0_status(dmaClearTx)) {
        dma_channel_acknowledge_irq0(dmaClearTx);
        clearInProcess = false;
    }
}

static void dma_init(void)
{
    int dma_chn = dma_claim_unused_channel(true);
    dma_channel_config c = dma_channel_get_default_config(dma_chn);
    channel_config_set_dreq(&c, spi_get_dreq(LCD_SPI_PORT, true));
    channel_config_set_transfer_data_size(&c, DMA_SIZE_16);
    channel_config_set_read_increment(&c, false);
    dma_channel_configure(dma_chn, &c, &spi_get_hw(LCD_SPI_PORT)->dr, NULL, 0, false);

    dma_channel_set_irq0_enabled(dma_chn, true);
    irq_set_exclusive_handler(DMA_IRQ_0, clearComplete);
    irq_set_enabled(DMA_IRQ_0, true);

    dmaClearTx = dma_chn;
}


static inline void st7789v_init(lcd_dev_t* dev)
{
    uint8_t reg = 0;
    uint32_t count = 0 , baudrate = 0;
    const uint8_t* cmd = register_init_list;

    /* GPIO Init */
    baudrate = st7789v_pin_init();

    /* DMA Init */
    dma_init();

    /* Reset LCD */
    st7789v_reset();

    /* tftWriteRegList(); */
    reg = 0x11;
    st7789v_write_cmd(&reg, 1);
    sleep_ms(120);
    do {
        count = cmd[0];
        st7789v_write_cmd(&cmd[1], count);
        cmd += (count + 1);
    } while(cmd[0]);

    /* Set TFT Dir */
    st7789v_set_dir(dev, LCD_DIRECTION_0);

    /* Clear TFT */
    spi_set_format(LCD_SPI_PORT, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    st7789v_clear_fullscreen(COLOR_BLACK);

    /* Open BackLight */
    /* freq_pwm = f_sys / period = fsys / ((TOP + 1) + DIV) */
    blkPwmSlice = pwm_gpio_to_slice_num(LCD_PIN_BLK);
    pwm_set_clkdiv(blkPwmSlice, 50.0f);     // Set DIV (125M / 50 = 25kHz)
    pwm_set_wrap(blkPwmSlice, 99);          // Set TOP
    pwm_set_chan_level(blkPwmSlice, PWM_CHAN_B, 100);
    pwm_set_enabled(blkPwmSlice, true);

    printf("ST7789V TFT Init Ok baudrate [%d] \n", baudrate);
}

void st7789v_dma_clear_blocking(uint16_t color)
{
    dma_channel_transfer_from_buffer_now(dmaClearTx, &color, ST7789V_SIZE);
    dma_channel_wait_for_finish_blocking(dmaClearTx);
}

static uint16_t clr;
void st7789v_dma_clear(uint16_t color)
{
    while(clearInProcess);
    clr = color;
    dma_channel_transfer_from_buffer_now(dmaClearTx, &clr, ST7789V_SIZE);
    clearInProcess = true;
}



/*
 * LCD Interface
 */

void lcd_init(lcd_dev_t* dev)
{
    st7789v_init(dev);
}

void lcd_set_backlight(uint8_t level)
{
    st7789v_set_blk(level);
}

void lcd_clear(uint16_t color)
{
//    st7789v_clear_fullscreen(color);
    st7789v_dma_clear(color);
//    st7789v_dma_clear_blocking(color);
}

void lcd_set_direction(lcd_dev_t* dev, lcd_dir_t dir)
{
    st7789v_set_dir(dev, dir);
}








