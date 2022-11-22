/*
 * DHT.h
 *
 *  Created on: Nov 20, 2022
 *      Author: student
 */

#ifndef SRC_DHT_H_
#define SRC_DHT_H_
#include "main.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim7;

typedef enum _dhtState
{
	//WAKING_UP_SIGNAL,
	AWAITING_RESPONSE_START,
	AWAITING_RESPONSE_END,
	RECEIVING_BITS,
	DATA_RECEIVED,

} DHT_STATE;

class DHT {
private:
	DHT_STATE state;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int counter;
	uint32_t lastFalling;

	void setGpioOutput();
	void setGpioExti();

public:
	DHT();
	virtual ~DHT();
	DHT(GPIO_TypeDef* gpiox, uint16_t gpio_pin);

	// Getters()
	DHT_STATE getState(){return state;}
	GPIO_TypeDef* getGpio(){return GPIOx;}
	uint16_t getPin(){return GPIO_Pin;}
	int getCounter(){return counter;}
	uint32_t getLastFalling(){return lastFalling;}

	int calculateTemp(int index);
	void wait(uint32_t time);
	int calculateTime(uint32_t _time);
	void startCommunication();
	void dataTransmission();
	void DHT_main();
//	void DHT_main_Async(DHT* dht);
	void Dht_readAsync();
//	void dhtInit(DHT* dht, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
//			no need for this init, in the constructor we init everything
	void Dht_onGpioInterrupt();
	void printTheTemprature();
	void returnTheTemprature(int* humidity, int* temp);

};

#endif /* SRC_DHT_H_ */
