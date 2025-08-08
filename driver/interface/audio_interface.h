#ifndef __AUDIOINTERFACE_H__
#define __AUDIOINTERFACE_H__

#include <stdint.h>

/**
 * @brief 初始化音频系统
 */
void audio_init(void);

/**
 * @brief 播放音频数据
 * @param data 指向音频数据的指针
 * @param size 音频数据长度（单位：字节）
 */
void audio_playback(void* data, uint32_t size);


#endif /* __AUDIOINTERFACE_H__ */

