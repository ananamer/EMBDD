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
	DHT_IN,
	DHT_OUT,
} DHT_STATE;

typedef struct _dht
{
	DHT_STATE state;
	int counter;
}DHT;



void wait(int time);
void startCommunication();
void dataTransmission();
int calculateTime(uint32_t _time);
void DHT_main();
int calculateTemp(int index);

#endif /* SRC_DHT_H_ */
