/*
 * hw.c
 *
 *  Created on: Feb 12, 2022
 *      Author: João
 */

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

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

void hw_delay_on_ms(uint32_t time_on_ms)
{
	HAL_Delay(time_on_ms);
}

void hw_delay_off_ms(uint32_t time_off_ms)
{
	HAL_Delay(time_off_ms);
}
