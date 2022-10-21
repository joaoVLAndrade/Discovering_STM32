/*
 * app.c
 *
 *  Created on: Feb 15, 2022
 *      Author: João
 */

#include <stdint.h>
#include <stdbool.h>

#include "app.h"
#include "hw.h"

void app_init(void)
{

}

void app_loop(void)
{
	uint32_t led_on_time_ms, led_off_time_ms;
	bool switch_0_state, switch_1_state;

	switch_0_state = hw_get_switch_0_state();
	switch_1_state = hw_get_switch_1_state();

	if(!switch_0_state && !switch_1_state)
	{
		led_on_time_ms = 100;
		led_off_time_ms = 100;
	}
	else if(!switch_0_state && switch_1_state)
	{
		led_on_time_ms = 300;
		led_off_time_ms = 150;
	}
	else if(switch_0_state && !switch_1_state)
	{
		led_on_time_ms = 600;
		led_off_time_ms = 300;
	}
	else
	{
		led_on_time_ms = 900;
		led_off_time_ms = 450;
	}

	hw_toggle_led_state();
	hw_delay(led_off_time_ms);
	hw_toggle_led_state();
	hw_delay(led_on_time_ms);

}
