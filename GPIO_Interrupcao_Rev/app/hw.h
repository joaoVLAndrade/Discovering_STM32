/*
 * hw.h
 *
 *  Created on: Feb 15, 2022
 *      Author: João
 */

#ifndef HW_H_
#define HW_H_

bool hw_toggle_switch_0_state(void);
bool hw_toggle_switch_1_state(void);

void hw_cpu_sleep(void);
void hw_delay(uint32_t time_ms);
void hw_led_state_set(bool state);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

uint32_t hw_get_tick_ms(void);

#endif /* HW_H_ */
