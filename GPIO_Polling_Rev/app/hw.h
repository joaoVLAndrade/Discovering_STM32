/*
 * hw.h
 *
 *  Created on: Feb 15, 2022
 *      Author: João
 */

#ifndef HW_H_
#define HW_H_

bool hw_get_switch_0_state(void);
bool hw_get_switch_1_state(void);

void hw_delay(uint32_t time_ms);
void hw_toggle_led_state(void);

#endif /* HW_H_ */
