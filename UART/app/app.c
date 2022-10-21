/*
 * app.c
 *
 *  Created on: Fev 21, 2022
 *      Author: João
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "ctype.h"

#include "cbf.h"
#include "shell.h"
#include "app.h"
#include "hw.h"


#define APP_DEBOUCING_TIME_MS 50
#define APP_UART_BUFFER_MAX   64

#define MAX_LED_TIME           5

static cbf_t cbf;
static uint8_t cbf_area[APP_UART_BUFFER_MAX];
static bool app_started = false;


void app_switch_interrupt(void)
{
	static uint32_t deboucing_time_ms = 0;

	if(!app_started)
		return;

	if((hw_tick_ms_get() - deboucing_time_ms) >= APP_DEBOUCING_TIME_MS)
	{
		deboucing_time_ms = hw_tick_ms_get();
	}
}

void app_tick_1ms(void)
{
	if(!app_started)
		return;
}

void app_init(void)
{
	shell_init();
	cbf_init(&cbf,cbf_area,APP_UART_BUFFER_MAX);
	hw_uart_init(&cbf);
	app_started = true;
}

void app_loop(void)
{

	static uint8_t n_blink = 8;
	static uint8_t tx_buffer[APP_UART_BUFFER_MAX];
	static uint8_t rx_buffer[APP_UART_BUFFER_MAX];
	uint8_t led_time[MAX_LED_TIME];
	uint8_t data = 0;
	uint32_t tx_size;
	uint32_t rx_size;
	cbf_status_t status;
	int aux_led_time = 0;
	int blink_time_ms = 0;


	tx_size = snprintf((char *)tx_buffer, APP_UART_BUFFER_MAX - 1, "get time\n");
	hw_uart_tx(tx_buffer,tx_size);
		// aguardando o ultimo byte ser transmitido pois caso contrario
		// o processador eh tao rapido que vai fazer o loop abaixo inteiro sem o ultimo
		// caracter ter chegado ainda
	rx_size = 0;
	hw_delay_ms(50);

	while(true)  //le o que tá no buffer circular
	{
		status = cbf_get(&cbf,&data);

		if((status == CBF_EMPTY) || (rx_size >= APP_UART_BUFFER_MAX))
			break;

		rx_buffer[rx_size++] = data;
	}

	for(int aux_buffer = 0; aux_buffer < rx_size; aux_buffer++)
	{
		if(isdigit(rx_buffer[aux_buffer]))
			led_time[aux_led_time++] = rx_buffer[aux_buffer];
	}
	while(aux_led_time < MAX_LED_TIME)
		led_time[aux_led_time++] = '\0';

	if(sscanf((char*)led_time,"%d",&blink_time_ms) == 1)
	{

		if(blink_time_ms >= 3200)
			blink_time_ms = 100;
		else
			blink_time_ms *= 2;

		int complete_blink = blink_time_ms*2;

		tx_size = snprintf((char *)tx_buffer, APP_UART_BUFFER_MAX - 1, "set time %d\n", blink_time_ms);
		hw_uart_tx(tx_buffer, tx_size);
		hw_delay_ms(complete_blink*n_blink);
	}

}
