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
extern ADC_HandleTypeDef hadc1;


void hw_timer_start()
{
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
}

void hw_adc_start(void)
{
	//HAL_ADCEx_Calibration_Start(&hadc1); Função invalida Black Pill
	HAL_ADC_Start(&hadc1);
}

void hw_set_timer(uint16_t led_time_ms)
{
	__HAL_TIM_SET_AUTORELOAD(&htim2, led_time_ms);
}

bool hw_adc_ch_read(uint16_t *adc_val)
{
	HAL_StatusTypeDef adc_hal_status;

	while(1)
	{
		adc_hal_status = HAL_ADC_PollForConversion(&hadc1, 100);
		if(adc_hal_status == HAL_OK)
		{
			*adc_val = (uint16_t) HAL_ADC_GetValue(&hadc1);
		}
		else if(adc_hal_status != HAL_OK)
			return false;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim1)
	{
		hw_adc_start();
		app_get_adc_values();
	}
	else if(htim == &htim2)
	{
		HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
		//__HAL_TIM_SET_COUNTER(&htim2, 0); //Reseta o temporizador de toggle
	}
}

