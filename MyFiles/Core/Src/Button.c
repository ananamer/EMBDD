/*
 * Button.c
 *
 *  Created on: Jun 23, 2022
 *      Author: student
 */
#include "Button.h"
#include "main.h"
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart2;

void buttonOnTimerInterrupt()
{

	static uint32_t press, release;
	if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == 0) {
		press = HAL_GetTick();
	}
	else {
		release = HAL_GetTick();
		if(( release - press) > 500){
			HAL_UART_Transmit( &huart2 , (uint8_t*) "long press\r\n" , 14 , 100);
		}
		else{
		HAL_UART_Transmit( &huart2 , (uint8_t*) "short press\r\n" , 15 , 100);
		}
	}

}


