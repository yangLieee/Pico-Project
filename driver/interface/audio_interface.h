#ifndef __AUDIOINTERFACE_H__
#define __AUDIOINTERFACE_H__

#include <stdint.h>



/* 音频初始化函数 */
void audio_init(void);

/* 播放音频函数 */
void audio_playback(void* data, uint32_t size);

#endif /* __AUDIOINTERFACE_H__ */

