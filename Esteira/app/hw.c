/*
 * hw.c
 *
 *  Created on: Mar 2, 2022
 *      Author: João
 */

#include <stdbool.h>
#include "main.h"
#include "app.h"

extern TIM_HandleTypeDef htim1;

void hw_input_capture_set(uint16_t count)
{
	__HAL_TIM_SET_COUNTER(&htim1, count);
}

void hw_input_capture_init(void)
{
	HAL_TIM_Base_Start(&htim1);
	hw_input_capture_set(0);
}

uint16_t hw_input_capture_get(void)
{
	return __HAL_TIM_GET_COUNTER(&htim1);
}

void hw_input_count_stop(void)
{
	hw_input_capture_set(0);
	HAL_TIM_Base_Stop_IT(&htim1);
}

void hw_led_state_set(bool state)
{
	GPIO_PinState LED_State = state ? GPIO_PIN_RESET : GPIO_PIN_SET;
	HAL_GPIO_WritePin(USER_LED_GPIO_Port,USER_LED_Pin,LED_State);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == USER_SW_0_Pin)
	{
		app_switch_0_interrupt();
	}
}

