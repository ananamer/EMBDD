/*
 * MyMain.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */
#include "MyMain.h"
#include "CliCommand.h"
#include "main.h"
#include "commTask.h"
#include "LED.h"
#include "CLI.h"
#include <stdio.h>
#include "BUZ.h"
#include "Button.h"
#include "DHT.h"
#include "cmsis_os.h"
#include "Flash.h"
#include "Rtc.h"
#include "DateTime.h"
#include "Manager.h"
#include <stdlib.h>
#include <string.h>
#include "SdCard.h"


// Extern
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern I2C_HandleTypeDef hi2c1;
extern CLI cli;


int numOfRecords = 0;
char RecordsArr[MAX_RECORDS][LEN_RECORD];


LED redLed(RED_GPIO_Port, RED_Pin, LED_OFF );
LED bluLed(BLU_GPIO_Port, BLU_Pin, LED_OFF);
BUZ buz(BUZ_OFF);
Button btn1(SW1_GPIO_Port, SW1_Pin);
Button btn2(SW2_GPIO_Port, SW2_Pin);
DHT dht(DHT11_GPIO_Port, DHT11_Pin);
Flash Thresholds(2, 0x08080000, 1, FLASH_TYPEPROGRAM_DOUBLEWORD);
DateTime initTime;

//--------------------------------
Manager* Monitor;
Rtc* rtc;
SdCard* LogSdCard;
char logBuffer[100];

//--------------------------------

void updateLogBuffer()
{
	DateTime dateTime;
	rtc->rtcGetTime(&dateTime);
	double currentTemp = dht.getTemp();
	SYSTEM_STATE monitorState = Monitor->getState() ;
	memset(logBuffer, 0, sizeof(logBuffer));
	if( monitorState == OK   ){
		sprintf(logBuffer, "OK! [%.2f] | %d:%d:%d - %d/%d/%d", currentTemp,
					dateTime.hours, dateTime.min    , dateTime.sec ,
					dateTime.day  , dateTime.month  , dateTime.year );
	}
	else if(monitorState == WARNING   ){
		sprintf(logBuffer, "Warning! [%.2f] | %d:%d:%d - %d/%d/%d", currentTemp,
					dateTime.hours, dateTime.min    , dateTime.sec ,
					dateTime.day  , dateTime.month  , dateTime.year );

	}
	else if(monitorState == CRITICAL){
		sprintf(logBuffer, "Critical! [%.2f] | %d:%d:%d - %d/%d/%d", currentTemp,
					dateTime.hours, dateTime.min    , dateTime.sec ,
					dateTime.day  , dateTime.month  , dateTime.year );

	}


}
void my_main()
{
	Monitor = new Manager(OK);
	rtc = new Rtc(&hi2c1, 0xD0);
	LogSdCard = new SdCard("Log.txt", "ErrorLog.txt");

//  Initial time -------------
//	initTime.hours   = 15 ;
//	initTime.min     = 35 ;
//	initTime.sec     =  0 ;
//	initTime.day     = 27 ;
//	initTime.month   = 11 ;
//	initTime.year    = 22 ;
//	initTime.weekDay =  1 ;
//	rtc->rtcSetTime(&initTime);
//  --------------------------

	HAL_TIM_Base_Init(&htim6);
	cli.CliInit();
	Thresholds.printThresHolds();
	bluLed.LedOn();
	printf("CHECK from my main\r\n");

}

void dhtTask()
{
	dht.DHT_main();

}

void mainTask()
{
	double currentTemp = dht.getTemp();
//	printf("\r\nFrom mainTask-temp = %f\r\n", currentTemp);

	if(currentTemp < Thresholds.getWarning() ){
		if( Monitor->getState() != OK){
			/* Transition to [OK] State:
			 * 		Blue led on, Red led off
			 * 		Buzzer off
			 * 		no need to write to log
			 */
			printf("State = [OK] \r\n");
			Monitor->setState(OK);
			bluLed.LedOn();
			redLed.LedOFF();
			buz.buzzStop();

		}
	}
	else if(currentTemp >= Thresholds.getWarning() &&
				currentTemp < Thresholds.getCritical() ){
			if( Monitor->getState() != WARNING   ){
				/* Transition to [WARNING] State:
				 * 		Blue led off, Red led on
				 * 		Buzzer off
				 * 		Write to log warning record
				 */
				printf("State = [WARNING] \r\n");
				Monitor->setState(WARNING);
				bluLed.LedOFF();
				redLed.LedOn();
				buz.buzzStop();
//				 * 		Write to log warning record

				char warningRecord[LEN_RECORD];
				DateTime warningTime;
				rtc->rtcGetTime(&warningTime);
//				*		Create the warning message
				sprintf(warningRecord, "Warning! [%.2f] | %d:%d:%d - %d/%d/%d", currentTemp,
										warningTime.hours, warningTime.min    , warningTime.sec ,
										warningTime.day  , warningTime.month  , warningTime.year );
//				*		Writing the record to the RecordsArray
//				*** WRITE TO SD *********************************************************************************
					updateLogBuffer();
					LogSdCard->write(LogSdCard->getErrorFileName(), logBuffer);

//				*** WRITE TO SD *********************************************************************************

				/*			Writing to the RecordsArr
 *
 *				if(numOfRecords < MAX_RECORDS-1){
					strcpy(RecordsArr[numOfRecords], warningRecord);
					numOfRecords++;
				}
				else{
					printf("Error! Out Of Memory- Please clear the log!\r\n");
				}
*/
			}

	}
	else if(currentTemp >= Thresholds.getCritical() ){
			if( Monitor->getState() != CRITICAL &&
					Monitor->getState() != CRITICAL_NO_BUZZER   ){
				/* Transition to [CRITICAL] State:
				 * 		Red led blink
				 * 		Buzzer on
				 * 		Write to log critical record
				 */

				printf("State = [CRITICAL] \r\n");
				Monitor->setState(CRITICAL);
				redLed.LedBlink();
				buz.buzzStart();
//				 * 		Write to log critical record

				char criticalRecord[LEN_RECORD];
				DateTime criticalTime;
				rtc->rtcGetTime(&criticalTime);
//				*		Create the warning message
				sprintf(criticalRecord, "Critical! [%.2f] | %d:%d:%d - %d/%d/%d", currentTemp,
										 criticalTime.hours, criticalTime.min    , criticalTime.sec ,
										 criticalTime.day  , criticalTime.month  , criticalTime.year );
//				*		Writing the record to the RecordsArray
//				*** WRITE TO SD *********************************************************************************
				updateLogBuffer();
				LogSdCard->write(LogSdCard->getErrorFileName(), logBuffer);

//				*** WRITE TO SD *********************************************************************************

/*			Writing to the RecordsArr
 *
 * 					if(numOfRecords < MAX_RECORDS-1){
					strcpy(RecordsArr[numOfRecords], criticalRecord);
					numOfRecords++;
					}
				else{
					printf("Error! Out Of Memory- Please clear the log!\r\n");
				}
*/
			}

	}


}
//				*** WRITE TO SD *********************************************************************************
//				updateLogBuffer();
//				logSdCard->write(LogSdCard->getErrorFileName(), logBuffer);
//				*** WRITE TO SD *********************************************************************************


void LogWriteTask()
{
	osDelay(1000);
//	LogSdCard->mount();
	while(1){
		updateLogBuffer();
		LogSdCard->write(LogSdCard->getFileName(), logBuffer);
		osDelay(60000);
	}
}

void LedTask()
{
	if(redLed.getState() == LED_BLINK){
		redLed.LedBlink();
	}
}



void measureTemp(void *argument)
{
	while(1){
//		dht.Dht_read();
		// TODO ------------------------------------------------------
		// this only prints the temp, I need to write it to the flash
	}
	osDelay(10000);
}



void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	if (pin == btn1.getPin()){
		// Buzzer Stop/Start
		if (HAL_GPIO_ReadPin(btn1.getGpio(), btn1.getPin()) == 0) {
			if(Monitor->getState() == CRITICAL){
				Monitor->setState(CRITICAL_NO_BUZZER);
				buz.buzzStop();
			}
		}
	}
}






//	while(1)
//	{
//		double tmp = dht.getTemp();
//		printf("from LedTask Temp = %f\r\n", tmp);
//
//		SYSTEM_STATE currentState =  Monitor->getState();
//		if(dht.getTemp() < (double)Thresholds.getWarning()){
//			// state ok
//			bluLed.LedOn();
//			redLed.LedOFF();
//			buz.buzzStop();
//		}
//		else {
//			bluLed.LedOFF();
//			if(dht.getTemp() < (double)Thresholds.getCritical() ){
//				// state warning
//				redLed.LedOn();
//				buz.buzzStart();
//			}
//			else{
//				redLed.LedBlink();
//				buz.buzzStart();
//			}
//		}
//		osDelay(1000);
//	}



/*
 * if ( temp<warning)
 * 		state = ok
 * else
 * 		if ( warning =< temp < critical)
 * 			state = warning
 *
 * else
 * 		if ( temp > critical && btn.state = 0)
 * 			state = critical
 * 		if ( temp > critical && btn.state = 1)
 * 			state = critical_no_buzzer
 *------------------------------------

 * switch Manager.getState
 * 		case OK
 * 				blu.on
 * 				red.off
 * 				buz.of
 * 		case WARNING
 * 				blu.off
 * 				red.on
 * 				buz.of
 * 				write a logRecord
 * 		case CRITICAL
 * 				blu.off
 * 				red.blink
 * 				buz.on
 * 				write a logRecord
 * 		case CRITICAL_NO_BUZZER
 * 				blu.off
 * 				red.blink
 * 				buz.off
 *
 *
 * */




