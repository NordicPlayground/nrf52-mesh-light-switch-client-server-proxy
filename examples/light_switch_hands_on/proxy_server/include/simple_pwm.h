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


/**
 * Initialize the simple PWM library
 *
 * Provide a pointer to a list of pins, and the number of pins. 
 * The list has to be between 1 and 4 items long. 
 * To invert an output, add PWM_PIN_INVERTED to the pin number.
 *
 * Usage example:
 *
 *       // Configure the PWM to use P0.12 non-inverted, and P0.13 inverted
 *       uint8_t pin_list[2] = {12, 13 | PWM_PIN_INVERTED};
 *       pwm_init(pin_list, 2);
 *
 * Note: When referring to the PWM outputs in the other functions the channel index is used, not the pin number. 
 *       In this example channel index 0 refers to P0.12, and channel index 1 refers to P0.13
 */
void pwm_init(uint8_t *pin_list, uint32_t pin_num);

/**
 * Set an output to a constant integer duty cycle, between 0 and SIMPLE_PWM_MAX_VALUE (20000 by default)
 *
 * The ch_index parameter is the index of the PWM channel, starting at 0, and not to be 
 * confused with the PIN number
 * Usage example
 *
 *       // Set the first PWM output to 50% duty cycle
 *       pwm_set_constant(0, SIMPLE_PWM_MAX_VALUE / 2);
 *
 */
void pwm_set_constant(uint32_t ch_index, uint32_t duty_cycle);

/**
 * Set an output to a constant floating point duty cycle, between 0.0f and 1.0f
 *
 * The ch_index parameter is the index of the PWM channel, starting at 0, and not to be 
 * confused with the PIN number
 * Usage example
 *
 *       // Set the first PWM output to 50% duty cycle
 *       pwm_set_constant(0, 0.5f);
 *
 */
void pwm_set_constant_f(uint32_t ch_index, float duty_cycle);

/**
 * Set an output to play a list of integer numbers in sequence, at a rate of 50Hz
 *
 * The ch_index parameter is the index of the PWM channel, starting at 0. 
 * The buffer parameter points to a list of numbers, and the length defines the size of the list. 
 * The loop_num parameter sets how many times the list should be repeated. 
 * Set loop_num to SIMPLE_PWM_LOOP_INFINITE to play the list forever. 
 *
 * Usage example
 *
 *       // Set the first PWM output to play a rapid fade in/out sequence 6 times
 *       uint16_t pwm_buf[] = {5000, 10000, 15000, 20000, 15000, 10000, 5000, 0};
 *       pwm_set_loop(0, pwm_buf, sizeof(pwm_buf) / sizeof(pwm_buf[0]), 6);
 *
 */
void pwm_set_loop(uint32_t ch_index, uint16_t *buffer, uint32_t length, uint32_t loop_num);

/**
 * Set an output to play a list of floating point numbers in sequence, at a rate of 50Hz
 *
 * The ch_index parameter is the index of the PWM channel, starting at 0. 
 * The buffer parameter points to a list of floating point numbers, and the length defines the size of the list. 
 * The loop_num parameter sets how many times the list should be repeated. 
 * Set loop_num to SIMPLE_PWM_LOOP_INFINITE to play the list forever. 
 *
 * Usage example
 *
 *       // Set the first PWM output to play a rapid fade in/out sequence 6 times
 *       float pwm_buf[] = {0.25f, 0.5f, 0.75f, 1.0f, 0.75f, 0.5f, 0.25f, 0.0f};
 *       pwm_set_loop(0, pwm_buf, sizeof(pwm_buf) / sizeof(pwm_buf[0]), 6);
 *
 */
void pwm_set_loop_f(uint32_t ch_index, float *buffer, uint32_t length, uint32_t loop_num);

/**
 * The following example buffers are provided to showcase typical LED features like fading in/out and pulsing 
 *
 * To use them simply call the defines, like this:
 *
 *      // Set the first PWM output to pulse slowly 10 times
 *      SIMPLE_PWM_PULSE_SLOW(0, 10);
 *
 *      // Have the second PWM output fade from 0 to 100% duty cycle
 *      SIMPLE_PWM_FADE_IN_SLOW(1);
 *
 */
#define SIMPLE_PWM_PULSE_SLOW(ch_index, count)  pwm_set_loop(ch_index, sinus_pulse_1000ms, 50, count)
#define SIMPLE_PWM_PULSE_FAST(ch_index, count)  pwm_set_loop(ch_index, sinus_pulse_500ms, 25, count)
#define SIMPLE_PWM_FADE_IN_SLOW(ch_index)       pwm_set_loop(ch_index, fade_in_1000ms, 50, 1)
#define SIMPLE_PWM_FADE_OUT_SLOW(ch_index)      pwm_set_loop(ch_index, fade_out_1000ms, 50, 1)

extern uint16_t sinus_pulse_1000ms[50];
extern uint16_t sinus_pulse_500ms[25];
extern uint16_t fade_in_1000ms[50];
extern uint16_t fade_out_1000ms[50];

#endif
