/*
 * DateTime.h
 *
 *  Created on: Nov 22, 2022
 *      Author: student
 */

#ifndef INC_DATETIME_H_
#define INC_DATETIME_H_

typedef struct DateTime_
{
	int sec;
	int min;
	int hours;
	int weekDay;
	int day;
	int month;
	int year;
} DateTime;

#endif /* INC_DATETIME_H_ */
