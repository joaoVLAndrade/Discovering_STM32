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
void hw_timer_start(TIM_HandleTypeDef *htim);
void hw_set_timer(uint16_t led_time);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* HW_H_ */
