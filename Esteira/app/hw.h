/*
 * hw.h
 *
 *  Created on: Mar 2, 2022
 *      Author: João
 */

#ifndef HW_H_
#define HW_H_

#include <stdbool.h>
#include <stdint.h>
#include "main.h"

void hw_led_state_set(bool state);
void hw_input_capture_init(void);
void hw_input_count_stop(void);
void hw_input_capture_set(uint16_t count);
uint16_t hw_input_capture_get(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* HW_H_ */
