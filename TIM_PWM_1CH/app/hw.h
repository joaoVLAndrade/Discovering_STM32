/*
 * hw.h
 *
 *  Created on: Mar 15, 2022
 *      Author: João
 */

#ifndef HW_H_
#define HW_H_

#include <stdbool.h>
#include <stdint.h>

void hw_pwm_start(void);
void hw_pwm_set_duty_cycle(uint32_t CCR);
uint32_t hw_get_tick_ms(void);
void hw_get_tick_1ms(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
bool hw_switch_get_state(void);

#endif /* HW_H_ */
