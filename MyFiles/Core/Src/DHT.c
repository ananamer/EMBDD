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
#include "DHT.h"
extern TIM_HandleTypeDef htim7;

#define SIZE 40

GPIO_InitTypeDef GPIO_InitStruct = {0};
GPIO_InitTypeDef gpioStruct ;
int dataBuff[40];
int integralRH, decimalRH;
int integralT, decimalT;
int checkSum;
uint32_t _time ;
uint32_t tmp_time;

// start the timer7
// GPIO pin is output
// --
// start communication
// write 0
// wait 18ms
// write 1
// wait 20-40 us
// GPIO PIN -> input
// --
// DHT sends response for 80us
// DHT pulls up and keep for 80 us
// --
// start the data transmission
// reset the counter, and start checking
// --
//	8bit integral RH data [0-7  ]
//	8bit decimal  RH data [8-15 ]
//	8bit integral T data  [16-23]
//	8bit decimal  T data  [24-31]
//	8bit check sum        [32-40]





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
	return _time > 100;
//	if( (_time >= 50) && (_time <= 90) ){
//		return 0;
//	}
//	else if((_time >= 110) && (_time <= 150)){
//		return 1;
//	}
//	return -1;
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
	HAL_TIM_Base_Start(&htim7);
	startCommunication();
	dataTransmission();
	printTheTemprature();
}

void DHT_main_Async(DHT* dht)
{
	Dht_readAsync(dht);

}

static void setGpioOutput (DHT * dht)
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin  = dht->GPIO_Pin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(dht->GPIOx, &gpioStruct);
}

static void setGpioExti (DHT * dht)
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin  = dht->GPIO_Pin;
	gpioStruct.Mode = GPIO_MODE_IT_FALLING;
	gpioStruct.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(dht->GPIOx, &gpioStruct);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}
void Dht_readAsync(DHT* dht)
{
	setGpioOutput(dht);

	HAL_TIM_Base_Start(&htim7);
	__HAL_TIM_SET_COUNTER(&htim7, 0);
	HAL_GPIO_WritePin(DHT_GPIO_Port, DHT_Pin, 0);
	wait(18000);
	HAL_GPIO_WritePin(DHT_GPIO_Port, DHT_Pin, 1);
	dht->state = AWAITING_RESPONSE_START;
	dht->lastFalling = __HAL_TIM_GET_COUNTER(&htim7);

	setGpioExti(dht);
	// when the DHT fall down to 0 the interrupt will handle
}

void dhtInit(DHT* dht, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	dht->state = AWAITING_RESPONSE_START; // WAKING_UP_SIGNAL;
	dht->GPIO_Pin = GPIO_Pin;
	dht->GPIOx = GPIOx;
	dht->counter = 0;
}



void Dht_onGpioInterrupt(DHT * dht)
{
	switch (dht->state) {
//		case WAKING_UP_SIGNAL:
//			dht->state = AWAITING_RESPONSE_START;
//			dht->lastFalling = __HAL_TIM_GET_COUNTER(&htim7);
//			break;
		case AWAITING_RESPONSE_START:
			dht->state = AWAITING_RESPONSE_END;
			dht->lastFalling = __HAL_TIM_GET_COUNTER(&htim7);
			break;
		case AWAITING_RESPONSE_END:
			dht->state = RECEIVING_BITS;
			dht->lastFalling = __HAL_TIM_GET_COUNTER(&htim7);
			break;
		case RECEIVING_BITS:
			if(dht->counter <40){
				tmp_time = __HAL_TIM_GET_COUNTER(&htim7);
				dataBuff[7-dht->counter]= calculateTime(tmp_time - dht->lastFalling);
				dht->counter++ ;
			}
			else{
				dht->state = DATA_RECEIVED;
			}
			dht->lastFalling = tmp_time;
			break;

		case DATA_RECEIVED:
			printTheTemprature();
			break;
		default:
			break;
	}
}

void printTheTemprature()
{
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
	printf("\r\n");
	printf("Humidity = %d.%d\r\n"
			 "Temprature  = %d.%d\r\n"
			"checkSum = %d \r\n"
			, integralRH, decimalRH, integralT, decimalT, checkSum      );
	if(checkSum == (integralRH + decimalRH + integralT + decimalT)){
		printf("CheckSum is OK !\r\n");
	}
	printf("\r\n ------------------------------------------------ \r\n");
}


//__HAL_TIM_SET_COUNTER(&htim7, 0);
//_time = __HAL_TIM_GET_COUNTER(&htim7);


//typedef enum _dhtState
//{
//	WAKING_UP_SIGNAL,
//	AWAITING_RESPONSE_START,
//	AWAITING_RESPONSE_END,
//	RECEIVING_BITS,
//	DATA_RECEIVED,
//} DHT_STATE;

//typedef struct _dht
//{
//	DHT_STATE state;
//	GPIO_TypeDef* GPIOx;
//	uint16_t GPIO_Pin;
//	int counter;
//}DHT;

//#define DHT_Pin GPIO_PIN_5
//#define DHT_GPIO_Port GPIOB

//	8bit integral RH data [0-7  ]
//	8bit decimal  RH data [8-15 ]
//	8bit integral T data  [16-23]
//	8bit decimal  T data  [24-31]
//	8bit check sum        [32-40]
