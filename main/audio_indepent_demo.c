#include <stdio.h>
#include "pico/stdlib.h"
#include "audio_interface.h"
#include "audio/mono_u8_8k.h"

void audio_demo(void)
{
    audio_init();
    while(1) {
        audio_playback(audio_data, audio_data_len);
        sleep_ms(5000);
    }
}
