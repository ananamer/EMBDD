/*
 * DHT.cpp
 *
 *  Created on: Nov 20, 2022
 *      Author: student
 */

#include "DHT.h"
#include "math.h"
#include "commTask.h"
#define SIZE 40

// Definitions
GPIO_InitTypeDef GPIO_InitStruct = {0};
int dataBuff[SIZE];
//uint32_t _time ;
uint32_t tmp_time;
int integralRH, decimalRH;
int integralT, decimalT;
int checkSum;

DHT::DHT() {
	// TODO Auto-generated constructor stub

}
DHT::~DHT() {
	// TODO Auto-generated destructor stub
}
DHT::DHT(GPIO_TypeDef* gpiox, uint16_t gpio_pin)
{
	GPIOx = gpiox;
	GPIO_Pin = gpio_pin;
	state = AWAITING_RESPONSE_START;
	counter = 0;
}
int DHT::calculateTemp(int index)
{
	int i , sum=0;
	int x = index;
	for(i=0; i<8; i++ ){
		sum += ( dataBuff[x] *(int)( pow(2, 7-i) ) );
		x++;
	}
	return sum;
}
void DHT::wait(uint32_t _time)
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
int DHT::calculateTime(uint32_t _time)
{
	return _time > 50;
}
void DHT::startCommunication()
{
//	HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET );
	wait(20000);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET );
	//wait(40);

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	uint32_t _time;
	__HAL_TIM_SET_COUNTER(&htim7, 0);
	while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1){
		_time = __HAL_TIM_GET_COUNTER(&htim7);
		if(_time > 100){
			printf("\r\n TIMEOUT\r\n");
			return;
		}
	}

	__HAL_TIM_SET_COUNTER(&htim7, 0);
	while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0){
		_time = __HAL_TIM_GET_COUNTER(&htim7);
			if(_time > 100){
				printf("\r\n TIMEOUT");
				return;
			}
	}

	__HAL_TIM_SET_COUNTER(&htim7, 0);
	while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1){
		_time = __HAL_TIM_GET_COUNTER(&htim7);
			if(_time > 100){
				printf("\r\n TIMEOUT");
				return;
			}
	}
	// start data transmission
	return;
}
void DHT::dataTransmission()
{
	uint32_t _time;
	for(int i=0; i<40; i++){

		__HAL_TIM_SET_COUNTER(&htim7, 0);
		while( HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0  ){ // while(0)
			_time = __HAL_TIM_GET_COUNTER(&htim7);
			if(_time > 100){
				printf("\r\n TIMEOUT");
				return;
			}
		}
		__HAL_TIM_SET_COUNTER(&htim7, 0);
		while( HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1  ){ // while(1)
			_time = __HAL_TIM_GET_COUNTER(&htim7);
			if(_time > 100){
				printf("\r\n TIMEOUT");
				return;
			}
		}
		dataBuff[i] = calculateTime(  _time);
	}//for
}
void DHT::DHT_main()
{
	HAL_TIM_Base_Start(&htim7);
	startCommunication();
	dataTransmission();
	printTheTemprature();
//	returnTheTemprature();
}
void DHT::setGpioOutput()
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin  = GPIO_Pin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOx, &gpioStruct);
}
void DHT::setGpioExti()
{
	GPIO_InitTypeDef gpioStruct = {0};

	gpioStruct.Pin  = GPIO_Pin;
	gpioStruct.Mode = GPIO_MODE_IT_FALLING;
	gpioStruct.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(GPIOx, &gpioStruct);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}
void DHT::Dht_readAsync()
{
	setGpioOutput();
	printf("from Dht_readAsync\r\n");
	HAL_TIM_Base_Start(&htim7);
	__HAL_TIM_SET_COUNTER(&htim7, 0);

	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	wait(18000);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	state = AWAITING_RESPONSE_START;
	lastFalling = __HAL_TIM_GET_COUNTER(&htim7);

	setGpioExti();
	// when the DHT fall down to 0 the interrupt will handle

}
void DHT::Dht_onGpioInterrupt()
{
	switch (state) {
//		case WAKING_UP_SIGNAL:
//			dht->state = AWAITING_RESPONSE_START;
//			dht->lastFalling = __HAL_TIM_GET_COUNTER(&htim7);
//			break;
		case AWAITING_RESPONSE_START:
			state = AWAITING_RESPONSE_END;
			lastFalling = __HAL_TIM_GET_COUNTER(&htim7);
			break;
		case AWAITING_RESPONSE_END:
			state = RECEIVING_BITS;
			lastFalling = __HAL_TIM_GET_COUNTER(&htim7);
			break;
		case RECEIVING_BITS:
			if(counter <40){
				tmp_time = __HAL_TIM_GET_COUNTER(&htim7);
				dataBuff[counter]= calculateTime(tmp_time - lastFalling);
				counter++ ;
			}
			else{
				state = DATA_RECEIVED;
			}
			lastFalling = tmp_time;
			break;

		case DATA_RECEIVED:
			printTheTemprature();
			state = AWAITING_RESPONSE_START;
			break;
		default:
			break;
	}
}
void DHT::returnTheTemprature(int* humidity, int* temp)
{
	*humidity = calculateTemp(0);
	*temp = calculateTemp(16);

}
void DHT::printTheTemprature()
{
	integralRH = calculateTemp(0);
	decimalRH =  calculateTemp(8);
	integralT = calculateTemp(16);
	decimalT =  calculateTemp(24);
	checkSum =  calculateTemp(32);
//	printf("\r\n ------------------------------------------------ \r\n");
//	printf("\r\n");
//	for(int i=0; i<40; i++){
//		if(i%8 == 0){
//			printf("\r\n");
//		}
//		printf("%d ," , dataBuff[i] );
//	}
//	printf("\r\n");
//	printf("Humidity = %d.%d\r\n"
//			 "Temprature  = %d.%d\r\n"
//			"checkSum = %d \r\n"
//			, integralRH, decimalRH, integralT, decimalT, checkSum      );
	printf("Humidity = %d.%d\r\n"
			 "Temprature  = %d.%d\r\n"
			, integralRH, decimalRH, integralT, decimalT);

	if(checkSum != (integralRH + decimalRH + integralT + decimalT)){
		printf("CheckSum ERROR !\r\n");
		printf(	"checkSum = %d \r\n", checkSum);
	}
//	printf("\r\n ------------------------------------------------ \r\n");
}

