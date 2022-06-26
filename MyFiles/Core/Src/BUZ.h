/*
 * BUZ.h
 *
 *  Created on: Jun 19, 2022
 *      Author: student
 */

#ifndef SRC_BUZ_H_
#define SRC_BUZ_H_
#include "main.h"


typedef enum _buzState
{
	BUZ_OFF,
	BUZ_ON,
} BUZ_STATE;

typedef struct _buz
{
	BUZ_STATE state;
	int counter;
	int maxCounter;
}BUZ;

void noteChange( int i);
void buzzerStart(BUZ* buz);
void buzInit(BUZ* buz);
void buzOnTimerInterrupt(BUZ* buz);
#endif /* SRC_BUZ_H_ */
