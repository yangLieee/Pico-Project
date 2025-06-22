#include <stdio.h>
#include "pwm_audio.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"

// 全局变量
static uint pwmSoundSlice = 0;
static int dmaPwmSetCC;

// 函数
void pwmInitDMA()
{
    dmaPwmSetCC = dma_claim_unused_channel(true);

    dma_channel_config c = dma_channel_get_default_config(dmaPwmSetCC);
    
    channel_config_set_dreq(&c, pwm_get_dreq(pwmSoundSlice));
    channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
    dma_channel_configure(dmaPwmSetCC, &c, (uint32_t *)&(pwm_hw->slice[pwmSoundSlice].cc), NULL, 0, false);
}

void pwmSoundOutputDmaBlocking(const uint32_t *sound, size_t len)
{
    dma_channel_wait_for_finish_blocking(dmaPwmSetCC);
    dma_channel_transfer_from_buffer_now(dmaPwmSetCC, (uint32_t *)sound, len);
}

void audio_init()
{
    // 设置左右声道的端口
    gpio_set_function(PWM_PIN_LEFT, GPIO_FUNC_PWM);
    gpio_set_function(PWM_PIN_RIGHT, GPIO_FUNC_PWM);

    // 获得PWM的载片
    pwmSoundSlice = pwm_gpio_to_slice_num(PWM_PIN_LEFT);

    // 设置PWM频率
    uint32_t sysFreq = clock_get_hz(clk_sys); // 默认125000000
    float clockDiv = sysFreq / (float)PWM_FREQ / (float)(PWM_TOP + 1);

    printf("Pwm sound freq: %d, top: %d, divider: %.2f\n", PWM_FREQ, PWM_TOP, clockDiv);

    pwm_set_clkdiv(pwmSoundSlice, clockDiv);

    // 设置TOP值
    pwm_set_wrap(pwmSoundSlice, PWM_TOP);

    // 设置双声道的CC
    pwm_set_both_levels(pwmSoundSlice, 0, 0);
    pwm_set_enabled(pwmSoundSlice, true);

    // DMA
//    pwmInitDMA();
}

void audio_playback(void* data, size_t len)
{
    const uint8_t* sound = (const uint8_t*) data;
    for (size_t index = 0; index < len; ++index)
    {
        pwm_set_both_levels(pwmSoundSlice, 0x7F, sound[index]);
        sleep_us(PWM_DELAY_TIME);
    }
}

