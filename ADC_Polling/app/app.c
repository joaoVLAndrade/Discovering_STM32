/*
 * app.c
 *
 *  Created on: Mar 2, 2022
 *      Author: João
 */

#include <stdbool.h>
#include <stdint.h>

#include "app.h"
#include "hw.h"

bool app_started = false;

void app_get_adc_values(void)
{
	uint16_t adc_ch3_val,adc_ch4_val;

	if(!app_started)
		return;
	hw_adc_start();
	hw_adc_ch_read(&adc_ch3_val);
	hw_adc_start();
	hw_adc_ch_read(&adc_ch4_val);
	app_led_set_time(adc_ch3_val,adc_ch4_val);
}

void app_led_set_time(uint16_t adc_ch3_val,uint16_t adc_ch4_val)
{
	uint16_t avg_value = (adc_ch3_val+adc_ch4_val)/2;
	//(Led_Max_Time_ms-Led_Min_Time_ms)Vd = ADC_Max_Value*Led_time_ms+ADC_Max_Value*Led_Min_Time_ms
	uint32_t led_time_ms = 2*((400*avg_value/4095)+200)-1; //Clock 42Mhz Prescaler 41999 -> count = 2*eq - 1
	hw_set_timer(led_time_ms);
}

void app_init()
{
	app_started = true;
	hw_timer_start();
}

void app_loop()
{

}
