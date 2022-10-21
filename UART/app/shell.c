/*
 * app.c
 *
 *  Created on: Nov 15, 2020
 *      Author: marce
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "cbf.h"
#include "shell.h"
#include "hw.h"

#define SHELL_UART_BUFFER_MAX 64
#define SHELL_MAX_ARGS        5

extern UART_HandleTypeDef huart1;

typedef struct shell_ctrl_s
{
	uint8_t cmd[SHELL_UART_BUFFER_MAX];
	uint32_t size;
} shell_ctrl_t;

static bool shell_started = false;
static shell_ctrl_t shell_ctrl = { 0 };
static uint32_t led_time_ms;

void shell_tick_1ms(void)
{
	static uint32_t led_time_cnt_ms = 0;

	if(!shell_started)
		return;

	led_time_cnt_ms++;

	if(led_time_cnt_ms >= led_time_ms)
	{
		led_time_cnt_ms = 0;
		hw_led_toggle();
	}
}

static void shell_uart_tx_byte(uint8_t c)
{
	USART_TypeDef *h = huart1.Instance;

	while(!(h->SR & UART_FLAG_TXE))
	{}

	h->DR = c;
}

void shell_uart_tx(uint8_t *buffer, uint32_t size)
{
	for(size_t pos = 0 ; pos < size ; pos++)
		shell_uart_tx_byte(buffer[pos]);
}

uint32_t shell_parse_args(uint8_t * const cmdline, uint32_t size, uint32_t *argc, uint8_t *argv[], uint32_t max_args)
{
    uint32_t n, m;

    n = m = 0;
    *argc = 0;

    while(cmdline[n] != '\0')
    {
        // remove initial spaces, if any
        while(isspace(cmdline[n]) && n < size)
            cmdline[n++] = '\0';

        // save where command/arguments starts
        m = n;

        // find end of command/parameters
        while(!isspace(cmdline[n]) && (n < size) && (cmdline[n] != '\0'))
            n++;

        // check end of string was reached, number of arguments reached or if we have an empty command
        if((n >= size) || (*argc >= max_args) || (m == n))
            break;

        // save command/arguments
        argv[*argc] = cmdline + m;
        *argc += 1;
    }

    // invalidate non used arguments
    for(n = *argc ; n < max_args ; n++)
        argv[n] = '\0';

    return *argc;
}

void shell_process(void)
{
	uint32_t argc;
	uint8_t *argv[SHELL_MAX_ARGS];
	bool error = true;

	if(shell_parse_args(shell_ctrl.cmd,shell_ctrl.size,&argc,(uint8_t **)argv,SHELL_MAX_ARGS))
	{
		if(argc == 3)
		{
			if((strncmp("set",(char*)argv[0],3) == 0) &&
			   (strncmp("time",(char*)argv[1],4) == 0))
			{
				int time_ms = 0;

				if(sscanf((char*)argv[2],"%d",&time_ms) == 1)
				{
					if(time_ms > 0)
					{
						led_time_ms = time_ms;
						shell_uart_tx((uint8_t*)"ok\n",3);
						error = false;
					}
				}
			}
		}
		else if(argc == 2)
		{
			if((strncmp("get",(char*)argv[0],3) == 0) &&
			   (strncmp("time",(char*)argv[1],4) == 0))
			{
				shell_ctrl.size = sprintf((char*)shell_ctrl.cmd,"time %u\n",(unsigned int)led_time_ms);
				shell_uart_tx(shell_ctrl.cmd,shell_ctrl.size);
				error = false;
			}
		}
	}

	if(error)
	{
		shell_uart_tx((uint8_t*)"error\n",6);
		error = false;
	}
}

void shell_add_byte(uint8_t c)
{
	shell_ctrl.cmd[shell_ctrl.size++] = c;

	// possivel comando completo encontrado
	if(c == '\n')
	{
		shell_ctrl.cmd[shell_ctrl.size-1] = '\0';
		shell_process();
		shell_ctrl.size = 0;
	}
	else
	{
		// perda de sincronismo ou frame grande e errado
		if(shell_ctrl.size >= SHELL_UART_BUFFER_MAX)
			shell_ctrl.size = 0;
	}
}

void shell_uart_interrupt(void)
{
	uint8_t c;
	uint32_t sr;
	USART_TypeDef *h = huart1.Instance; // hardcoded, pode ser melhorado

	// ler o status register e trata erros até que desapareçam
	// (o manual manda ler o SR e em seguida DR em caso de erro)
	sr = h->SR;
	while(sr & (UART_FLAG_ORE | UART_FLAG_PE | UART_FLAG_FE | UART_FLAG_NE))
	{
		sr = h->SR;
		c = h->DR;
	}

	// se sem erros e com dado recebido ... pegar o dado e colocar no buffer
	if(sr & UART_FLAG_RXNE)
	{
		c = h->DR;

		if(shell_started)
			shell_add_byte(c);
	}
}

void shell_disable_interrupts(void)
{
	HAL_NVIC_DisableIRQ(USART1_IRQn);
}

void shell_enable_interrupts(void)
{
    HAL_NVIC_SetPriority(USART1_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_NVIC_ClearPendingIRQ(USART1_IRQn);
}

void shell_uart_init(void)
{
	shell_disable_interrupts();

    // habilitando interrupcoes para casos de erro
    // (Frame error, noise error, overrun error)
    huart1.Instance->CR3 |= USART_CR3_EIE;
    // habilitando interrupcoes para paridade e dados novos
    huart1.Instance->CR1 |= USART_CR1_PEIE | USART_CR1_RXNEIE;

	shell_enable_interrupts();
}

void shell_init(void)
{
	shell_ctrl.size = 0;
	led_time_ms = 100;
	shell_uart_init();

	shell_started = true;
}
