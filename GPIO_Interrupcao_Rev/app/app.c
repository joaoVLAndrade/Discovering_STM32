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

#define APP_DEBOUNCING_TIME_MS 100

volatile uint32_t led_on_time_ms = 100,led_off_time_ms = 100;
volatile bool switch_0_state, switch_1_state;

bool app_started = false;

void app_switch_0_interrupt(void)
{
	static uint32_t debouncing_time_ms = 0;

	if(hw_get_tick_ms() - debouncing_time_ms >= APP_DEBOUNCING_TIME_MS)
		switch_0_state = hw_toggle_switch_0_state();
	debouncing_time_ms = hw_get_tick_ms();
}

void app_switch_1_interrupt(void)
{
	static uint32_t debouncing_time_ms = 0;

	if(hw_get_tick_ms() - debouncing_time_ms >= APP_DEBOUNCING_TIME_MS)
		switch_1_state = hw_toggle_switch_1_state();
	debouncing_time_ms = hw_get_tick_ms();
}


void app_get_tick(void)
{
	static uint32_t led_time_cnt_ms = 0;

	if(!app_started)
		return;

	led_time_cnt_ms++;

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

	if(led_off_time_ms >= led_time_cnt_ms)
		hw_led_state_set(false);
	else if(led_on_time_ms+ led_off_time_ms >= led_time_cnt_ms)
		hw_led_state_set(true);
	else
		led_time_cnt_ms = 0;

}

void app_init(void)
{
	app_started = true;
}

void app_loop(void)
{
	hw_cpu_sleep();
}

