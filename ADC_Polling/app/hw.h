/*
 * hw.h
 *
 *  Created on: Mar 2, 2022
 *      Author: João
 */

#ifndef HW_H_
#define HW_H_

#include <stdint.h>
#include "main.h"

void hw_led_toggle(void);
void hw_timer_start();

void hw_set_timer(uint16_t led_time_ms);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

void hw_adc_start(void);
bool hw_adc_ch_read(uint16_t *adc_val);

#endif /* HW_H_ */
