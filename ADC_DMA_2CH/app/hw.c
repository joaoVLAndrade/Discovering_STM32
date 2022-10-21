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
extern TIM_HandleTypeDef htim3;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;


void hw_timer_start()
{
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
}

void hw_adc_start(uint16_t *values,uint32_t size)
{
	HAL_TIM_Base_Start(&htim3);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*) values, size);
}

void hw_adc_calibration(void)
{
	__HAL_DMA_DISABLE_IT(&hdma_adc1, DMA_IT_HT);
}

void hw_adc_stop(void)
{
	HAL_TIM_Base_Stop(&htim3);
	HAL_ADC_Stop_DMA(&hadc1);
}

void hw_set_timer(uint16_t led_time_ms)
{
	__HAL_TIM_SET_AUTORELOAD(&htim2, led_time_ms);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim1)
	{
		app_get_adc_values();
	}
	else if(htim == &htim2)
	{
		HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
		//__HAL_TIM_SET_COUNTER(&htim2, 0); //Reseta o temporizador de toggle
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	app_set_adc_finished();
}

