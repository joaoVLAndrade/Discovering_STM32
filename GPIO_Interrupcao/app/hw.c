/*
 * hw.c
 *
 *  Created on: Feb 13, 2022
 *      Author: João
 */

#include "main.h"
#include "app.h"
#include <stdint.h>
#include <stdbool.h>

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == USER_SW_0_Pin || GPIO_Pin == USER_SW_1_Pin)
	{
		app_switches_interrupt();
	}
}


void hw_switches_get_state(bool *sw_state_0, bool *sw_state_1)
{
	GPIO_PinState switch_0_state = HAL_GPIO_ReadPin(USER_SW_0_GPIO_Port,USER_SW_0_Pin);
	GPIO_PinState switch_1_state = HAL_GPIO_ReadPin(USER_SW_1_GPIO_Port,USER_SW_1_Pin);

	*sw_state_0 = switch_0_state == GPIO_PIN_SET? false : true;
	*sw_state_1 = switch_1_state == GPIO_PIN_SET? false : true;
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

