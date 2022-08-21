/*
 * MyMain.c
 *
 *  Created on: Aug 11, 2022
 *      Author: student
 */
#include "MyMain.h"
#include "main.h"
#include "commTask.h"
#include "Cli.h"
#include "stm32l4xx_hal.h"
#include "Rtc.h"
extern I2C_HandleTypeDef hi2c1;

//#include "stm32l476xx.h"



extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;

// *********************************
/*
 * typedef struct DateTime_
{
	int sec;
	int min;
	int hours;
	int weekDay;
	int day;
	int month;
	int year;
} DateTime;

 * */

void myMain()
{


	DateTime initTime;

	initTime.hours = 0 ;
	initTime.min =   0 ;
	initTime.sec =   0 ;

	initTime.day =	 1 ;
	initTime.month = 1 ;
	initTime.year =  20;


	rtcSetTime(&initTime);


	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ( TIM6_DAC_IRQn);
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_NVIC_EnableIRQ( TIM3_IRQn);

	cliInit();
	while(1){
		if (commTask()) {
				handleCommand();
		}
	}

	return;
}
///**********************************

// rtc
// DateTime starting time





//#define BLULED_Pin GPIO_PIN_5
//#define BLULED_GPIO_Port GPIOA
//#define REDLED_Pin GPIO_PIN_6
//#define REDLED_GPIO_Port GPIOA
//#define SW1_Pin GPIO_PIN_10
//#define SW1_GPIO_Port GPIOA
//#define SW1_EXTI_IRQn EXTI15_10_IRQn
//#define SW2_Pin GPIO_PIN_3
//#define SW2_GPIO_Port GPIOB
//#define SW2_EXTI_IRQn EXTI3_IRQn
