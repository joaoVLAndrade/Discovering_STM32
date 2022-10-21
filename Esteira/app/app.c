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
#define APP_DEBOUNCING_TIME_MS 100

bool app_started = false;
volatile bool box_full = false;

uint16_t max_obj = 5;

void app_switch_0_interrupt(void)
{
	if(!app_started || box_full == false)
		return;
	hw_input_capture_init();
	box_full = false;
	hw_led_state_set(true);//Reinicia a esteira
}

void app_init()
{
	app_started = true;
	hw_input_capture_init();
}

void app_loop()
{
	uint16_t cnt_obj = hw_input_capture_get();
	if(cnt_obj > max_obj && !box_full)
	{
		hw_led_state_set(false); //Para a esteira
		hw_input_count_stop();
		box_full = true;
	}
}
