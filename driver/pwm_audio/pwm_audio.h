#ifndef __PWMAUDIO_H__
#define __PWMAUDIO_H__

#include <stdint.h>

// PWM
#define PWM_PIN_LEFT    12
#define PWM_PIN_RIGHT   13
#define PWM_FREQ        8000  // 声道频率，可以试试11025、22050、44100
#define PWM_DELAY_TIME  (1000000 / PWM_FREQ)
#define PWM_TOP         255     // 实际的值为TOP + 1

#endif  /* __PWMAUDIO_H__ */

