
include_directories(${DRIVER_PREFIX}/interface)

set(DRIVER_SRC  ${DRIVER_PREFIX}/lcd/st7789v/st7789v.c
                ${DRIVER_PREFIX}/touch/CST816/CST816.c
                ${DRIVER_PREFIX}/pwm_audio/pwm_audio.c
    )

