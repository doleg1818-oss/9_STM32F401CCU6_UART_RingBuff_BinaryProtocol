/*
 * command_parser.c
 *
 *  Created on: Jun 3, 2026
 *      Author: Olegd
 */


#include "api_command.h"
#include "main.h"
#include "led.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CMD_PING		0x01
#define CMD_LED_SET		0x02
#define CMD_GET_STATUS	0x03

extern UART_HandleTypeDef huart1;

void procces_packed(protocol_packed_t *packed)
{
	if(packed == NULL)
	{
		return;
	}

	switch(packed->type)
	{
		case CMD_PING:
		{
			const char msg[] = "PONG..\n\r";
			HAL_UART_Transmit(&huart1,(uint8_t*) msg, sizeof(msg)-1, HAL_MAX_DELAY);
			break;
		}
		case CMD_LED_SET:
		{
			if(packed->payload_len == 1)
			{
				bool led_state = (packed->payload[0] != 0);
				led_on_off(led_state);
				const char msg[] = "LED OK\n\r";
				HAL_UART_Transmit(&huart1,(uint8_t*) msg, sizeof(msg)-1, HAL_MAX_DELAY);
			}
			else
			{
				const char msg[] = "LED ERR\n\r";
				HAL_UART_Transmit(&huart1,(uint8_t*) msg, sizeof(msg)-1, HAL_MAX_DELAY);
			}
			break;
		}
		case CMD_GET_STATUS:
		{
			char msg[64] = {0,};
			snprintf(msg, sizeof(msg), "STATUS LED %d \n\r",
					HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET ? 1 : 0);
			HAL_UART_Transmit(&huart1,(uint8_t*) msg, sizeof(msg)-1, HAL_MAX_DELAY);
			break;
		}
		default:
		{
			const char msg[] = "Wrong CMD !!!\n\r";
			HAL_UART_Transmit(&huart1,(uint8_t*) msg, sizeof(msg)-1, HAL_MAX_DELAY);
			break;
		}


	}
}

