/*
 * BUZ.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_BUZ_H_
#define SRC_BUZ_H_
#include "main.h"

extern TIM_HandleTypeDef htim3;

typedef enum _buzState
{
	BUZ_OFF,
	BUZ_ON,
} BUZ_STATE;


class BUZ {

	BUZ_STATE State = BUZ_OFF;
//	int counter;
//	int maxCounter;
public:
	BUZ();
	BUZ(BUZ_STATE state);
	virtual ~BUZ();
	void buzzStart();
	void buzzStop();

	BUZ_STATE getState(){return State;}

};

#endif /* SRC_BUZ_H_ */
