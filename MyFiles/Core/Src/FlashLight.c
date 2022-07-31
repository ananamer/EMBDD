
/*
 * FlashLight.c
 *
 *  Created on: 9 Jun 2022
 *      Author: student
 */


//	STATE_OFF,
//	STATE_FULL,
//	STATE_HALF,
//	STATE_BLINK,

#include "FlashLight.h"
#include "main.h"
#include "MainTimer.h"

extern TIM_HandleTypeDef htim6;
int bright_set;

FlashLightState changeState()
{
	static FlashLightState FLS = STATE_OFF;

	switch (FLS)
	{
	    case STATE_OFF:
	    	FLS =STATE_FULL;
	    	break;
	    case STATE_FULL:
	    	FLS =STATE_HALF;
	   	    break;
	    case STATE_HALF:
	    	FLS =STATE_BLINK;
	    	break;
	    case STATE_BLINK:
	    	FLS =STATE_OFF;
	   	    break;
	    default:
	    	FLS =STATE_OFF;
	    	break;
	}
	return FLS;
}


void LedOFF()
	{
	    HAL_TIM_Base_Stop_IT(&htim6);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);

	}
void ledFULL()
	{
	    HAL_TIM_Base_Stop_IT(&htim6);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);

	}
void ledHALF()
	{
		__HAL_TIM_SET_COUNTER(&htim6, 0);
	    __HAL_TIM_SET_AUTORELOAD(&htim6, 100);
		HAL_TIM_Base_Start_IT(&htim6);
	 	//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		//HAL_Delay(10);

	}
void ledBLINK()
	{
		__HAL_TIM_SET_COUNTER(&htim6, 0);
		__HAL_TIM_SET_AUTORELOAD(&htim6, 3000);
		HAL_TIM_Base_Start_IT(&htim6);
		 //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		 //HAL_Delay(100);
	}


void LedHandle(FlashLightState FLS)
{
	switch (FLS)
	{
	    case STATE_OFF:
	    	LedOFF();
	    	break;
	    case STATE_FULL:
	    	ledFULL();
	   	    break;
	    case STATE_HALF:
	    	ledHALF();
	    	break;
	    case STATE_BLINK:
	    	ledBLINK();
	   	    break;
	    default:
	    	LedOFF();
	    	break;
	}
}

void setBrightness(int Brightness)
{
	bright_set = Brightness;
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim6, 10);
	HAL_TIM_Base_Start_IT(&htim6);

}








































