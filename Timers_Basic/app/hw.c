/*
 * hw.c
 *
 *  Created on: Mar 2, 2022
 *      Author: João
 */

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

void hw_timer_start(TIM_HandleTypeDef *htim)
{
	HAL_TIM_Base_Start_IT(htim);
}
void hw_set_timer(uint16_t led_time)
{
	__HAL_TIM_SET_AUTORELOAD(&htim1, led_time);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim1)
	{
		HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
		__HAL_TIM_SET_COUNTER(&htim1, 0); //Reseta o temporizador de toggle
	}
	else if(htim == &htim2)
	{
		__HAL_TIM_SET_COUNTER(&htim2, 0); //Reseta o temporizador de debouncing
		HAL_TIM_Base_Stop_IT(&htim2); //Para o temporizador de debouncing
		HAL_NVIC_EnableIRQ(EXTI0_IRQn); //Reativa a interrupção do botão
		app_change_led_blink_time();//Após o tempo de debouncing o tempo de ON/OFF do led é alterado
	}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == USER_SW_0_Pin)
	{
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		app_switch_0_interrupt();
	}
}

