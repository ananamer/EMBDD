/*
 * MyMain.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "MyMain.h"
#include "CliCommand.h"
#include "main.h"
#include "commTask.h"
#include "LED.h"
#include "CLI.h"
#include <stdio.h>
#include "BUZ.h"

LED redLed(RED_GPIO_Port, RED_Pin, LED_ON );
LED bluLed(BLU_GPIO_Port, BLU_Pin, LED_ON);
BUZ buz(BUZ_OFF);

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;

extern CLI cli;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * tim)
{
	if(tim == &htim7){
		// if the red state is blinking
		if(redLed.getState() == LED_BLINK){
			HAL_GPIO_TogglePin(redLed.getGpio(), redLed.getPin());
		}
		if(bluLed.getState() == LED_BLINK){
			HAL_GPIO_TogglePin(bluLed.getGpio(), bluLed.getPin());
		}
	}
	else if(tim == &htim3){
			printf("BZZZZ\r\n");
	}
}

void my_main()
{
	printf("CHECK from my main\r\n");
	cli.CliInit();
	while(1){
		if(commTask()){
			handleCommand();
		}
	}
}

