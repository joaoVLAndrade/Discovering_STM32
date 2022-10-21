/*
 * hw.c
 *
 *  Created on: Feb 15, 2022
 *      Author: João
 */

#include <stdbool.h>
#include <stdint.h>

#include "hw.h"
#include "main.h"

bool hw_get_switch_0_state(void)
{
	GPIO_PinState state = HAL_GPIO_ReadPin(USER_SW_0_GPIO_Port, USER_SW_0_Pin);
	return state == GPIO_PIN_SET? false: true;
}

bool hw_get_switch_1_state(void)
{
	GPIO_PinState state = HAL_GPIO_ReadPin(USER_SW_1_GPIO_Port, USER_SW_1_Pin);
	return state == GPIO_PIN_SET ? false: true;
}

void hw_toggle_led_state(void)
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
}

void hw_delay(uint32_t time_ms)
{
	HAL_Delay(time_ms);
}
