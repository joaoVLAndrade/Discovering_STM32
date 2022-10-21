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

#define ADC_SAMPLES_N 10
#define ADC_CHANNEL_N 2

volatile bool adc_finished = false;

uint16_t adc_raw_data[ADC_SAMPLES_N] = {0};
bool app_started = false;

void app_set_adc_finished(void)
{
	adc_finished = true;
	hw_adc_stop();
}

void app_get_adc_values()
{
	hw_adc_start(adc_raw_data, ADC_SAMPLES_N);
}

void app_average_adc_value(uint16_t *adc_raw_val, uint16_t *adc_avg_ch1, uint16_t *adc_avg_ch2)
{
	uint16_t cnt = 0;
	uint32_t sum_temp[ADC_CHANNEL_N] = {0, 0};

	while(cnt < ADC_SAMPLES_N)
	{
		for(uint8_t i = 0; i < ADC_CHANNEL_N; i++)
			sum_temp[i] = sum_temp[i] + adc_raw_val[cnt+i];
		cnt+=ADC_CHANNEL_N;
	}
	for(uint8_t i = 0; i < ADC_CHANNEL_N; i++)
		sum_temp[i] = sum_temp[i] / (ADC_SAMPLES_N / ADC_CHANNEL_N);

	*adc_avg_ch1 = (uint16_t) sum_temp[0];
	*adc_avg_ch2 = (uint16_t) sum_temp[1];
}

void app_led_set_time(uint16_t adc_ch1_val,uint16_t adc_ch2_val)
{
	uint16_t final_avg_value = (adc_ch1_val+adc_ch1_val)/2;
	//(Led_Max_Time_ms-Led_Min_Time_ms)Vd = ADC_Max_Value*Led_time_ms+ADC_Max_Value*Led_Min_Time_ms
	uint16_t led_time_ms = 2*((400*final_avg_value/4095)+200)-1; //Clock 42Mhz Prescaler 41999 -> count = 2*eq - 1
	hw_set_timer(led_time_ms);
}

void app_init()
{
	app_started = true;
	hw_adc_calibration();
	hw_timer_start();
}

void app_loop()
{
	uint16_t adc_avg_ch1, adc_avg_ch2;
	if(adc_finished)
	{
		adc_finished = false;
		app_average_adc_value(adc_raw_data, &adc_avg_ch1, &adc_avg_ch2);
		app_led_set_time(adc_avg_ch1, adc_avg_ch2);
	}

}
