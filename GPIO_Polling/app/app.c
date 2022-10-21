/*
 * app.c
 *
 *  Created on: Feb 12, 2022
 *      Author: João
 */

#include <stdint.h>
#include "app.h"
#include "hw.h"
#include <stdbool.h>


void app_init(void)
{

}
void app_loop(void)
{
	uint32_t led_on_time_ms;
	uint32_t led_off_time_ms;
	bool switch_0_state,switch_1_state;
	hw_switches_get_state(&switch_0_state, &switch_1_state);


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

	hw_led_state_set(true);
	hw_delay_on_ms(led_on_time_ms);
	hw_led_state_set(false);
	hw_delay_off_ms(led_off_time_ms);
}
