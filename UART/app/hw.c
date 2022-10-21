/*
 * hw.c
 *
 *  Created on: Nov 15, 2020
 *      Author: marce
 */

#include <stdint.h>
#include <stdbool.h>
#include "cbf.h"
#include "main.h"
#include "app.h"

extern UART_HandleTypeDef huart2;

static cbf_t *hw_uart_cbf = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		app_switch_interrupt();
	}
}

bool hw_switch_state_get(void)
{
	GPIO_PinState switch_state = HAL_GPIO_ReadPin(USER_SW_GPIO_Port,USER_SW_Pin);

	if(switch_state == GPIO_PIN_SET)
		return true;
	else
		return false;
}

void hw_led_toggle(void)
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port,USER_LED_Pin);
}

void hw_led_state_set(bool state)
{
	GPIO_PinState led_state = state ? GPIO_PIN_RESET : GPIO_PIN_SET;

	HAL_GPIO_WritePin(USER_LED_GPIO_Port,USER_LED_Pin,led_state);
}

void hw_delay_ms(uint32_t time_ms)
{
	HAL_Delay(time_ms);
}

uint32_t hw_tick_ms_get(void)
{
	return HAL_GetTick();
}

void hw_cpu_sleep(void)
{
	__WFI();
}

void hw_uart_disable_interrupts(void)
{
	HAL_NVIC_DisableIRQ(USART2_IRQn);
}

void hw_uart_enable_interrupts(void)
{
    HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
    HAL_NVIC_ClearPendingIRQ(USART2_IRQn);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
}

void hw_uart_init(cbf_t *cbf)
{
	hw_uart_disable_interrupts();

    // habilitando interrupcoes para casos de erro
    // (Frame error, noise error, overrun error)
    huart2.Instance->CR3 |= USART_CR3_EIE;
    // habilitando interrupcoes para paridade e dados novos
    huart2.Instance->CR1 |= USART_CR1_PEIE | USART_CR1_RXNEIE;

	hw_uart_cbf = cbf;

	hw_uart_enable_interrupts();
}

void hw_uart2_interrupt(void)
{
	uint8_t c;
	uint32_t sr;
	USART_TypeDef *h = huart2.Instance; // hardcoded, pode ser melhorado

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

		if(hw_uart_cbf)
			cbf_put(hw_uart_cbf,c);
	}
}

static void hw_uart_tx_byte(uint8_t c)
{
	USART_TypeDef *h = huart2.Instance;

	// garante que o shift register esta vazio
	while(!(h->SR & UART_FLAG_TXE))
	{}

	// coloca o valor no shift register
	h->DR = c;
}


void hw_uart_tx(uint8_t *buffer, uint32_t size)
{
	for(size_t pos = 0 ; pos < size ; pos++)
		hw_uart_tx_byte(buffer[pos]);
}

