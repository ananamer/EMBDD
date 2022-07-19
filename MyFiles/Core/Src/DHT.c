/*
 * DHT.c
 *
 *  Created on: 19 Jul 2022
 *      Author: student
 */

#include "main.h"
#include <stdio.h>
#include "commTask.h"
#include <math.h>

extern TIM_HandleTypeDef htim7;

#define SIZE 40

GPIO_InitTypeDef GPIO_InitStruct = {0};
// start the timer7
// GPIO pin is output

// start communication
// write 0
// wait 18ms
// write 1
// wait 20-40 us
// GPIO PIN -> input

// DHT sends response for 80us
// DHT pulls up and keep for 80 us

// start the data transmission
// reset the counter, and start checking

//	8bit integral RH data [0-7  ]
//	8bit decimal  RH data [8-15 ]
//	8bit integral T data  [16-23]
//	8bit decimal  T data  [24-31]
//	8bit check sum        [32-40]

GPIO_InitTypeDef gpioStruct ;
int dataBuff[40];
uint32_t _time ;

int calculateTemp(int index){
	int i , sum=0;
	int x = index;
	for(i=0; i<8; i++ ){
		sum += ( dataBuff[x] *(int)( pow(2, 7-i) ) );
		x++;
	}
	return sum;
}

void wait(int _time)
{
	uint32_t ms_time ;
	__HAL_TIM_SET_COUNTER(&htim7, 0);
	while(1){
		ms_time = __HAL_TIM_GET_COUNTER(&htim7);
		if(ms_time >= _time){
			return;
		}
	}
}

int calculateTime(uint32_t _time)
{
	if( (_time >= 0) && (_time <= 40) ){
		return 0;
		}
	else if((_time >= 60) && (_time <= 100)){
		return 1;
	}
//return 0;
}

void startCommunication()
{
	HAL_GPIO_WritePin(DHT_GPIO_Port, DHT_Pin, 0);
	wait(18000);
	HAL_GPIO_WritePin(DHT_GPIO_Port, DHT_Pin, 1);
	wait(40);

	GPIO_InitStruct.Pin = DHT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	__HAL_TIM_SET_COUNTER(&htim7, 0);
	while (HAL_GPIO_ReadPin(DHT_GPIO_Port, DHT_Pin) == 1){
		_time = __HAL_TIM_GET_COUNTER(&htim7);
		if(_time > 100){
			printf("\r\n TIMEOUT");
			return;
		}
	}

	__HAL_TIM_SET_COUNTER(&htim7, 0);
	while (HAL_GPIO_ReadPin(DHT_GPIO_Port, DHT_Pin) == 0){
		_time = __HAL_TIM_GET_COUNTER(&htim7);
			if(_time > 100){
				printf("\r\n TIMEOUT");
				return;
			}
	}

	__HAL_TIM_SET_COUNTER(&htim7, 0);
	while (HAL_GPIO_ReadPin(DHT_GPIO_Port, DHT_Pin) == 1){
		_time = __HAL_TIM_GET_COUNTER(&htim7);
			if(_time > 100){
				printf("\r\n TIMEOUT");
				return;
			}

	}
	// start data transmission

	return;
}

void dataTransmission()
{

	for(int i=0; i<40; i++){

		__HAL_TIM_SET_COUNTER(&htim7, 0);
		while( HAL_GPIO_ReadPin(DHT_GPIO_Port, DHT_Pin) == 0  ){ // while(0)
			_time = __HAL_TIM_GET_COUNTER(&htim7);
			if(_time > 100){
				printf("\r\n TIMEOUT");
				return;
			}
		}
		__HAL_TIM_SET_COUNTER(&htim7, 0);
		while( HAL_GPIO_ReadPin(DHT_GPIO_Port, DHT_Pin) == 1  ){ // while(1)
			_time = __HAL_TIM_GET_COUNTER(&htim7);
			if(_time > 100){
				printf("\r\n TIMEOUT");
				return;
			}
		}
		dataBuff[i] = calculateTime(  _time);



		}//for
}


void DHT_main()
{
	int integralRH, decimalRH;
	int integralT, decimalT;
	int checkSum;


	HAL_TIM_Base_Start(&htim7);
	startCommunication();
	dataTransmission();

	integralRH = calculateTemp(0);
	decimalRH =  calculateTemp(8);
	integralT = calculateTemp(16);
	decimalT =  calculateTemp(24);
	checkSum =  calculateTemp(32);
	printf("\r\n ------------------------------------------------ \r\n");
	printf("\r\n{");
	for(int i=0; i<40; i++){
		if(i%8 == 0){
			printf("\r\n");
		}
		printf("%d ," , dataBuff[i] );
	}
	printf("\r\n}");


	printf("internalRH = %d \t decimalRH = %d \r\n"
	   		 "internalT  = %d \t decimalT  = %d \r\n"
			"\tcheckSum = %d \r\n"
			, integralRH, decimalRH, integralT, decimalT, checkSum      );
	printf("\r\n ------------------------------------------------ \r\n");
}


//	8bit integral RH data [0-7  ]
//	8bit decimal  RH data [8-15 ]
//	8bit integral T data  [16-23]
//	8bit decimal  T data  [24-31]
//	8bit check sum        [32-40]
