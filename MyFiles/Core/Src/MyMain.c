/*
 * MyMain.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */
#include "main.h"
#include "BUZ.h"
#include "LED.h"
#include "RGB.h"
#include "FlashLight.h"
#include "stm32l4xx_hal.h"
#include "Clock.h"
#include "BUZ.h"
#include <stdio.h>
#include "Button.h"
#include "commTask.h"
#include "cli.h"
#include "DHT.h"
#include "MainTimer.h"

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart2;
extern int bright_set;

LED ledB, ledR;
RGB rgb1, rgb2, rgb3;
CLOCK clk;
BUZ buz;
DHT _dht;

int volLenCounter = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * tim)
{
	if(tim == &htim6){
		ClockOnTimerPeriod(&clk);

		ledOnTimerInterrupt(&ledB);
		ledOnTimerInterrupt(&ledR);

		rgbOnTimerInterrupt(&rgb1); // GREEN
		rgbOnTimerInterrupt(&rgb2); // RED
		rgbOnTimerInterrupt(&rgb3); // BLUE

		buzOnTimerInterrupt(&buz);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	if(pin == GPIO_PIN_5){
		 Dht_onGpioInterrupt(&_dht);
	}
	else if (pin == SW1_Pin){
		// Buzzer Start *************
	if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == 0) {
		HAL_TIM_Base_Start(&htim3);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
		buzzerStart(&buz);
	}
	// Buzzer End *************
	 buttonOnTimerInterrupt();
	}
	 // Button Start *************
//	static uint32_t press, release;
//	if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == 0) {
//		press = HAL_GetTick();
//	}
//	else {
//		release = HAL_GetTick();
//		if(( release - press) > 500){
//			HAL_UART_Transmit( &huart2 , (uint8_t*) "long press\r\n" , 14 , 100);
//		}
//		else{
//		HAL_UART_Transmit( &huart2 , (uint8_t*) "short press\r\n" , 15 , 100);
//		}
//	}
	// Button Press Start *************



	// LED Start *************
	ledStart(&ledR);
	ledStart(&ledB);
	// LED End *************
}


void My_Main ()
{

//	DHT_main();
//	ClockInit(&clk);

	buzInit(&buz);

	ledInit(&ledB, LD2_GPIO_Port, LD2_Pin); // BLUE
	ledInit(&ledR, LD3_GPIO_Port, LD3_Pin); // RED

	rgbInit(&rgb1, RGB1_GPIO_Port, RGB1_Pin); // GREEN
	rgbInit(&rgb2, RGB2_GPIO_Port, RGB2_Pin); // RED
	rgbInit(&rgb3, RGB3_GPIO_Port, RGB3_Pin); // BLUE

	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ( TIM6_DAC_IRQn );
	HAL_NVIC_EnableIRQ( TIM3_IRQn  );
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start(&htim3);

	cliInit();

	dhtInit(&_dht, DHT_GPIO_Port, DHT_Pin);

	while(1){
		if (commTask()) {
				handleCommand();
		}
	}


}


