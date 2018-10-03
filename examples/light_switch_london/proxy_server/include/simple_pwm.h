#ifndef __SIMPLE_PWM_H
#define __SIMPLE_PWM_H

#include <stdint.h>
#include <stdbool.h>
#include "nrf_drv_pwm.h"

#define PWM_PIN_INVERTED            NRF_DRV_PWM_PIN_INVERTED
#define SIMPLE_PWM_CHANNEL_NUM      4
#define SIMPLE_PWM_MAX_VALUE        20000
#define SIMPLE_PWM_PIN_UNUSED       0xFFFFFFFF
#define SIMPLE_PWM_LOOP_INFINITE    0

// Sample PWM buffers
extern uint16_t                                 sinus_pulse_1000ms[50];
#define SIMPLE_PWM_PULSE_SLOW(ch_index, count)  pwm_set_loop(ch_index, sinus_pulse_1000ms, 50, count)

extern uint16_t                                 sinus_pulse_500ms[25];
#define SIMPLE_PWM_PULSE_FAST(ch_index, count)  pwm_set_loop(ch_index, sinus_pulse_500ms, 25, count)

extern uint16_t                                 fade_in_1000ms[50];
#define SIMPLE_PWM_FADE_IN_SLOW(ch_index)       pwm_set_loop(ch_index, fade_in_1000ms, 50, 1)

extern uint16_t                                 fade_out_1000ms[50];
#define SIMPLE_PWM_FADE_OUT_SLOW(ch_index)      pwm_set_loop(ch_index, fade_in_1000ms, 50, 1)

typedef struct
{
    bool constant;
    uint16_t *data_ptr;
    float    *data_ptr_float;
    uint32_t  data_length;
    uint32_t  data_index;
    uint32_t  loop_counter;
}simple_pwm_channel_config_t;

void pwm_init(uint8_t *pin_list, uint32_t pin_num);

void pwm_set_constant(uint32_t ch, uint32_t duty_cycle);

void pwm_set_constant_f(uint32_t ch, float duty_cycle);

void pwm_set_loop(uint32_t ch, uint16_t *buffer, uint32_t length, uint32_t loop_num);

void pwm_set_loop_f(uint32_t ch, float *buffer, uint32_t length, uint32_t loop_num);

#endif
