/*
 * hw.c
 *
 *  Created on: Mar 15, 2022
 *      Author: João
 */

#include "main.h"
#include "app.h"
#include "hw.h"

extern TIM_HandleTypeDef htim1;
#define TURN_OFF_TIME 3000

void hw_pwm_start(void)
{
	HAL_TIM_PWM_Init(&htim1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void hw_pwm_set_duty_cycle(uint32_t CCR)
{
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, CCR);
}

uint32_t hw_get_tick_ms(void)
{
	return HAL_GetTick();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == USER_SW_Pin)
	{
		app_led_control();
	}
}

void hw_get_tick_1ms(void)
{
	app_led_turn_off();
}

bool hw_switch_get_state(void)
{
	return HAL_GPIO_ReadPin(USER_SW_GPIO_Port, USER_SW_Pin);
}

