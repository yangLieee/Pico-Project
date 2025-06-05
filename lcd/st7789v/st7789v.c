#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "st7789v.h"
#include "st7789v_reg_def.h"

TFTDevice dev = {
    .width  = ST7789V_WIDTH,
    .height = ST7789V_HEIGHT,
};

static uint8_t blkPwmSlice;

static inline void tftSetDcAndCs(bool dc, bool cs)
{
    gpio_put_masked( (1 << LCD_PIN_DC) | (1 << LCD_PIN_CS), (cs << LCD_PIN_CS) | (dc << LCD_PIN_DC));
}

// CMD[0] = Command
// CMD[1...n] = Param
static inline void tftWriteCmd(const uint8_t *cmd, size_t len)
{
    tftSetDcAndCs(0, 0);
    spi_write_blocking(LCD_SPI_PORT, cmd, 1);
    tftSetDcAndCs(0, 1);

    // With Param
    if(len > 1) {
        tftSetDcAndCs(1, 0);
        spi_write_blocking(LCD_SPI_PORT, &cmd[1], len-1);
        tftSetDcAndCs(1, 1);
    }
}

static inline void tftWriteData(const uint16_t data)
{
    uint8_t array[2];
    tftSetDcAndCs(1, 0);

    array[0] = (data >> 8) & 0xff;
    array[1] = (data & 0xff);
    spi_write_blocking(LCD_SPI_PORT, array, 2);

    tftSetDcAndCs(1, 1);
}

void tftSetWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    uint8_t cmd;
    uint16_t temp;
    // Width
    temp = x + width;
    if(temp > dev.width) {
        temp = dev.width;
    }
    --temp;

    cmd = 0x2a;
    tftWriteCmd(&cmd, 1);
    tftWriteData(x);
    tftWriteData(temp);

    // Height
    temp = y + height;
    if(temp > dev.height) {
        temp = dev.height;
    }
    --temp;

    cmd = 0x2b;
    tftWriteCmd(&cmd, 1);
    tftWriteData(y);
    tftWriteData(temp);

    // Write LCD
    cmd = 0x2c;
    tftWriteCmd(&cmd, 1);
}

void tftSetDirection(TFTDirection dir)
{
    uint8_t temp = 0;
    switch(dir) {
        case ST7789V_DIRECTION_0:
            dev.width  = ST7789V_WIDTH;
            dev.height = ST7789V_HEIGHT;
            temp =  MADCTL_MX;
            break;
        case ST7789V_DIRECTION_90:
            dev.width  = ST7789V_HEIGHT;
            dev.height = ST7789V_WIDTH;
            temp =  MADCTL_MV;
            break;
        case ST7789V_DIRECTION_180:
            dev.width  = ST7789V_WIDTH;
            dev.height = ST7789V_HEIGHT;
            temp =  MADCTL_MY;
            break;
        case ST7789V_DIRECTION_270:
            dev.width  = ST7789V_HEIGHT;
            dev.height = ST7789V_WIDTH;
            temp =  MADCTL_MX | MADCTL_MY | MADCTL_MV;
            break;
        default:
            break;
    }

    temp |= MADCTL_RGB;
    uint8_t cmd[2] = {0x36, temp};
    tftWriteCmd(cmd, 2);

    tftSetWindow(0, 0, dev.width, dev.height);
}

void tftClear(uint16_t color)
{
    size_t fillsize = ST7789V_SIZE;
    for(size_t i=0; i < fillsize; i++) {
        tftWriteData(color);
    }
}

void tftPlot(uint16_t x, uint16_t y, uint16_t color)
{
    tftSetWindow(x, y, 1, 1);
    tftWriteData(color);
}

void tftDrawArray(uint16_t* src, size_t len)
{
    for(size_t i=0; i < len; i++) {
        tftWriteData(src[i]);
    }
}


void tftInit(void)
{
    uint32_t baudrate = spi_init(LCD_SPI_PORT, LCD_SPI_BAUDRATE);

    /* GPIO Init */
    gpio_init(LCD_PIN_CS);
    gpio_init(LCD_PIN_DC);
    gpio_init(LCD_PIN_BLK);
    gpio_init(LCD_PIN_RST);
    /* gpio_init_masked((1<<LCD_PIN_DC) | (1<<LCD_PIN_BLK) | (1<<LCD_PIN_RST)); */
    gpio_set_function(LCD_PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(LCD_PIN_SCK, GPIO_FUNC_SPI);

    /* GPIO Dir */
    gpio_set_dir(LCD_PIN_CS,  true);
    gpio_set_dir(LCD_PIN_DC,  true);
    gpio_set_dir(LCD_PIN_BLK, true);
    gpio_set_dir(LCD_PIN_RST, true);

    /* GPIO Init Value */
    gpio_put(LCD_PIN_CS, true);

    /* Reset LCD */
    gpio_put(LCD_PIN_RST, false);
    sleep_ms(100);
    gpio_put(LCD_PIN_RST, true);
    sleep_ms(100);
 
#if 1
    /* tftWriteRegList(); */
    const uint8_t initCmd[] = {
        /* number cmd param */
        0x81, 0x11,                // delay 120 
        3, 0x36,    0x00, 0xA0,    // degree 0
        2, 0x3A,    0x05,
        6, 0xB2,    0x0C, 0x0C, 0x00, 0x33, 0x33,
        2, 0xB7,    0x35,
        2, 0xBB,    0x32,       // Vcom = 1.35v
        2, 0xC2,    0x01,
        2, 0xC3,    0x15,       // GVDD = 4.8v Color Deep
        2, 0xC4,    0x20,       // VDV  0x20: 0v
        2, 0xC6,    0x0f,       // 0x0F 60Hz
        3, 0xD0,    0xA4, 0xA1,
        15,0xE0,    0xD0, 0x08, 0x0E, 0x09, 0x09, 0x05, 0x31, 0x33, 0x48, 0x17, 0x14, 0x15, 0x31, 0x34,
        15,0xE1,    0xD0, 0x08, 0x0E, 0x09, 0x09, 0x15, 0x31, 0x33, 0x48, 0x17, 0x14, 0x15, 0x31, 0x34,
        0x81, 0x31,
        0x81, 0x29,
        0x00,
    };
    const uint8_t *item = initCmd;
    uint8_t count, temp;
    while(*item) {
        temp  = *item++;
        count = temp & 0x7f;

        /* printf("len %d cmd 0x%x \n", count, item[0]); */
        tftWriteCmd(item, count);
        item += count;

        if(temp == 0x81) {
            sleep_ms(120);
        }
     }
#endif

    /* Open BackLight */
#if 0
    gpio_put(LCD_PIN_BLK, true);
#else
    gpio_set_function(LCD_PIN_BLK, GPIO_FUNC_PWM);
    blkPwmSlice = pwm_gpio_to_slice_num(LCD_PIN_BLK);
    pwm_set_clkdiv(blkPwmSlice, 50.0f);     // 125M / 50 = 25kHz
    pwm_set_wrap(blkPwmSlice, 99);          // set cc
    pwm_set_chan_level(blkPwmSlice, PWM_CHAN_B, 100); 
    pwm_set_enabled(blkPwmSlice, true);

#endif

    /* Set TFT Dir */
    tftSetDirection(ST7789V_DIRECTION_0);

    /* Clear TFT */
    tftClear(ST7789V_BLUE);

    printf("ST7789V TFT Init Ok. baudrate [%d] \n", baudrate);
}

void tftSetBlkLight(uint16_t level)
{
    if(level > 0 || level < 100) {
        pwm_set_chan_level(blkPwmSlice, PWM_CHAN_B, level); 
    }
}

