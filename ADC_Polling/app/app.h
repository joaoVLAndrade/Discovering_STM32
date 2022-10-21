/*
 * app.h
 *
 *  Created on: Mar 2, 2022
 *      Author: João
 */

#ifndef APP_H_
#define APP_H_

void app_init(void);
void app_loop(void);
void app_get_adc_values(void);
void app_led_set_time(uint16_t adc_ch3_val,uint16_t adc_ch4_val);

#endif /* APP_H_ */
