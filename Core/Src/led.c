/*
 * led.c
 *
 *  Created on: Jul 7, 2026
 *      Author: Olegd
 */

#include "led.h"
#include "main.h"

void led_on_off(bool state)
{
	if(state == false)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	}
}
