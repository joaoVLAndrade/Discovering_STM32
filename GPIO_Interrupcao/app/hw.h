/*
 * hw.h
 *
 *  Created on: Feb 13, 2022
 *      Author: João
 */

#ifndef HW_H_
#define HW_H_

#include <stdbool.h>

void hw_cpu_sleep(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void hw_switches_get_state(bool *state_0, bool *state_1);
void hw_led_state_set(bool state);

uint32_t hw_get_tick_ms(void);

#endif /* HW_H_ */
