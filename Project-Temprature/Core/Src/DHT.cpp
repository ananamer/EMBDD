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
	temperature = 0.0;
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
			printf("\r\n TIMEOUT1\r\n");
			return;
		}
	}

	__HAL_TIM_SET_COUNTER(&htim7, 0);
	while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0){
		_time = __HAL_TIM_GET_COUNTER(&htim7);
			if(_time > 100){
				printf("\r\n TIMEOUT2");
				return;
			}
	}

	__HAL_TIM_SET_COUNTER(&htim7, 0);
	while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1){
		_time = __HAL_TIM_GET_COUNTER(&htim7);
			if(_time > 100){
				printf("\r\n TIMEOUT3");
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
				printf("\r\n TIMEOUT4");
				return;
			}
		}
		__HAL_TIM_SET_COUNTER(&htim7, 0);
		while( HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1  ){ // while(1)
			_time = __HAL_TIM_GET_COUNTER(&htim7);
			if(_time > 100){
				printf("\r\n TIMEOUT5");
				return;
			}
		}
		dataBuff[i] = calculateTime(  _time);
	}
}
void DHT::DHT_main()
{
	HAL_TIM_Base_Start(&htim7);
	startCommunication();
	dataTransmission();
	Dht_read();
//	printTheTemprature();
}
void DHT::printTheTemprature()
{
//  THIS DONE IN THE measureTemp()
	//-----------------------------
	integralRH = calculateTemp(0);
	decimalRH =  calculateTemp(8);
	integralT = calculateTemp(16);
	decimalT =  calculateTemp(24);
	checkSum =  calculateTemp(32);
	//-----------------------------


	printf("Humidity = %d.%d\r\n"
			 "Temprature  = %d.%d\r\n"
			, integralRH, decimalRH,
				integralT, decimalT);


	if(checkSum != (integralRH + decimalRH + integralT + decimalT)){
		printf("CheckSum ERROR !\r\n");
		printf(	"checkSum = %d \r\n", checkSum);
	}
//	printf("\r\n ------------------------------------------------ \r\n");
}
void DHT::Dht_read()
{
	integralRH = calculateTemp(0);
	decimalRH =  calculateTemp(8);
	integralT = calculateTemp(16);
	decimalT =  calculateTemp(24);
	checkSum =  calculateTemp(32);
	temperature = (double)integralT +  (double)decimalT/100 ;


//	printf("integralT = %d\r\n", integralT);
//	printf("decimalT = %d\r\n", decimalT);
//	printf("Temp = %f\r\n", temperature);

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
