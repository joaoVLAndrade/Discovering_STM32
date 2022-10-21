/*
 * hw.h
 *
 *  Created on: Feb 12, 2022
 *      Author: João
 */

#ifndef HW_H_
#define HW_H_

#include <stdbool.h>

void hw_switches_get_state(bool *state_0, bool *state_1);
void hw_led_state_set(bool state);
void hw_delay_on_ms(uint32_t time_on_ms);
void hw_delay_off_ms(uint32_t time_off_ms);

#endif /* HW_H_ */
