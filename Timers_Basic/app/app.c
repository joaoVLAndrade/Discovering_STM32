/*
 * app.c
 *
 *  Created on: Mar 2, 2022
 *      Author: João
 */

#include "app.h"
#include "hw.h"
#include "main.h"

#include <stdbool.h>
#include <stdint.h>

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

uint16_t led_time = 499;
bool app_started = false;

void app_switch_0_interrupt(void)
{
	if(!app_started)
		return;
	hw_timer_start(&htim2); //Inicia o tempo de debouncing
}

void app_change_led_blink_time(void)
{
	if(!app_started)
			return;
	if(led_time == 499)
		led_time = 999;
	else
		led_time = 499;
	hw_set_timer(led_time);
}

void app_init()
{
	app_started = true;
	hw_timer_start(&htim1);
}

void app_loop()
{

}
