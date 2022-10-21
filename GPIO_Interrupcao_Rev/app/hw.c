/*
 * hw.c
 *
 *  Created on: Feb 15, 2022
 *      Author: João
 */

#include <stdbool.h>
#include <stdint.h>

#include "app.h"
#include "hw.h"
#include "main.h"

bool state_0 = true;//switch 1 inital state - Pull_up
bool state_1 = true;//switch 1 inital state - Pull_up

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == USER_SW_0_Pin)
	{
		app_switch_0_interrupt();
	}
	else
	{
		app_switch_1_interrupt();
	}
}

bool hw_toggle_switch_0_state(void)
{
	state_0 = !state_0;
	return !state_0;
}

bool hw_toggle_switch_1_state(void)
{
	state_1 = !state_1;
	return !state_1;
}

void hw_led_state_set(bool state)
{
	GPIO_PinState LED_State = state ? GPIO_PIN_RESET : GPIO_PIN_SET;
	HAL_GPIO_WritePin(USER_LED_GPIO_Port,USER_LED_Pin,LED_State);
}

uint32_t hw_get_tick_ms(void)
{
	return HAL_GetTick();
}

void hw_cpu_sleep(void)
{
	__WFI();
}
