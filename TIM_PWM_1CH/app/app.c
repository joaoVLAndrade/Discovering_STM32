/*
 * app.c
 *
 *  Created on: Mar 15, 2022
 *      Author: João
 */

#include <stdio.h>
#include <stdbool.h>
#include "hw.h"
#include "app.h"

#define APP_DEBOUNCING_TIME_MS 50
#define CNT 20

bool app_started = false;

volatile bool flag_led_state = false;
volatile  uint16_t ccr_duty_cycle = 0;
volatile bool reset_flag;

void app_led_control(void)
{
	static uint32_t debouncing_time_ms = 0;

	if(!app_started || reset_flag)
		return;

	if(hw_get_tick_ms() - debouncing_time_ms >= APP_DEBOUNCING_TIME_MS)
	{
		ccr_duty_cycle = ccr_duty_cycle + (CNT/10);
		if(ccr_duty_cycle <= CNT)
			hw_pwm_set_duty_cycle(ccr_duty_cycle);
		else
		{
			ccr_duty_cycle = 0;
			hw_pwm_set_duty_cycle(ccr_duty_cycle);
		}
		debouncing_time_ms = hw_get_tick_ms();
	}
}

void app_led_turn_off()
{
	static uint32_t aux_time = 0;
	bool User_SW_State;
	reset_flag = false;
	if(!app_started)
		return;
	User_SW_State = hw_switch_get_state();
	if(User_SW_State == false)
	{
		aux_time++;
		if(aux_time >= 3000)
		{
			hw_pwm_set_duty_cycle(0);
			aux_time = 0;
			ccr_duty_cycle = 0;
			reset_flag = true;
		}
	}
	else
		aux_time = 0;
}

void app_init(void)
{
	hw_pwm_start();
	app_started = true;
}

void app_loop(void)
{
	;
}
