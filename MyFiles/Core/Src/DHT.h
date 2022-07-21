/*
 * DHT.h
 *
 *  Created on: 19 Jul 2022
 *      Author: student
 */

#ifndef SRC_DHT_H_
#define SRC_DHT_H_

typedef enum _dhtState
{
	//WAKING_UP_SIGNAL,
	AWAITING_RESPONSE_START,
	AWAITING_RESPONSE_END,
	RECEIVING_BITS,
	DATA_RECEIVED,

} DHT_STATE;

typedef struct _dht
{
	DHT_STATE state;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int counter;
	uint32_t lastFalling;
}DHT;


int calculateTemp(int index);
void wait(int time);
int calculateTime(uint32_t _time);
void startCommunication();
void dataTransmission();
void DHT_main();
void DHT_main_Async(DHT* dht);
void Dht_readAsync(DHT* dht);
void dhtInit(DHT* dht, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Dht_onGpioInterrupt(DHT * dht);
void printTheTemprature();
#endif /* SRC_DHT_H_ */
