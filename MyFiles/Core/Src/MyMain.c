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

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart2;
extern int bright_set;

int i=0;

LED ledB;
LED ledR;

RGB rgb1;
RGB rgb2;
RGB rgb3;

CLOCK clk;

BUZ buz;

int _write(int fd, char* ptr, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t *) ptr, len, HAL_MAX_DELAY);
    return len;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * tim)
{
	if(tim == &htim6){
		ClockOnTimerPeriod(&clk);

		ledOnTimerInterrupt(&ledB);
		ledOnTimerInterrupt(&ledR);

		rgbOnTimerInterrupt(&rgb1);
		rgbOnTimerInterrupt(&rgb2);
		rgbOnTimerInterrupt(&rgb3);

		buzOnTimerInterrupt(&buz);
	}

}

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{

	// Buzzer Start *************
	if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == 0) {
		HAL_TIM_Base_Start(&htim3);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	buzzerStart(&buz);
	ledStart(&ledR);
	ledStart(&ledB);
	}
	// Buzzer End *************

	// Button Start *************
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
	// Button Press Start *************

	// LED Start *************

	// LED End *************
}


void My_Main ()
{


	ClockInit(&clk);

	ledInit(&ledB, LD2_GPIO_Port, LD2_Pin); // BLUE
	ledInit(&ledR, LD3_GPIO_Port, LD3_Pin); // RED

	rgbInit(&rgb1, RGB1_GPIO_Port, RGB1_Pin);
	rgbInit(&rgb2, RGB2_GPIO_Port, RGB2_Pin);
	rgbInit(&rgb2, RGB3_GPIO_Port, RGB3_Pin);

	buzInit(&buz);


	//	  char word [20];
	//	  scanf("%s", word);
	//	  if(strcmp(word, "start") == 0){
	//
	//		  ledR->state = LED_ON;
	//	  }
	//	  else if(strcmp(word, "stop") == 0){
	//		  ledR->state = LED_OFF;
	//	  }
	//	  else if(strcmp(word, "blink") == 0){
	//	  	  ledR->state = LED_BLINK;
	//	    }


	//	rgbBlink(&rgb1, 100);
	//	rgbBlink(&rgb2, 400);
	//	rgbBlink(&rgb3, 200);

	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ( TIM6_DAC_IRQn );
	HAL_NVIC_EnableIRQ( TIM3_IRQn  );
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start(&htim3);
	//HAL_NVIC_EnableIRQ(  TIM7_IRQn  );



	//HAL_TIM_Base_Start_IT(&htim7);
	//	__HAL_TIM_SET_AUTORELOAD(&htim7, 1);


}
