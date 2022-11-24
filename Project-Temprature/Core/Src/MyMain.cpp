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

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern I2C_HandleTypeDef hi2c1;

LED redLed(RED_GPIO_Port, RED_Pin, LED_OFF );
LED bluLed(BLU_GPIO_Port, BLU_Pin, LED_OFF);
BUZ buz(BUZ_OFF);
Button btn1(SW1_GPIO_Port, SW1_Pin);
Button btn2(SW2_GPIO_Port, SW2_Pin);
DHT dht(DHT11_GPIO_Port, DHT11_Pin);
Flash Thresholds(2, 0x08080000, 1, FLASH_TYPEPROGRAM_DOUBLEWORD);

DateTime date_time;
Rtc* rtc = new Rtc(&hi2c1, 0xD0);
//#define SW1_Pin GPIO_PIN_10
//#define SW1_GPIO_Port GPIOA
//#define SW2_Pin GPIO_PIN_5
//#define SW2_GPIO_Port GPIO
//#define DHT11_Pin GPIO_PIN_5
//#define DHT11_GPIO_Port GPIOB


DateTime initTime;

extern CLI cli;

void my_main()
{


	initTime.hours = 0 ;
	initTime.min =   0 ;
	initTime.sec =   0 ;
	initTime.day =	 1 ;
	initTime.month = 1 ;
	initTime.year =  20;



	HAL_TIM_Base_Init(&htim6);
	cli.CliInit();
	Thresholds.printThresHolds();

	printf("CHECK from my main\r\n");

}
void dhtTask()
{
	dht.DHT_main();
// this will print the temp every second because its called from the mymain task


}

void TimeTask()
{
//	print the time each second
//	rtc.rtcGetTime();
//  with os delay 1000
}
void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	if (pin == btn1.getPin()){
		// Buzzer Stop/Start
		if (HAL_GPIO_ReadPin(btn1.getGpio(), btn1.getPin()) == 0) {

			if(buz.getState() == BUZ_ON){
				buz.buzzStop();
			}
			else if(buz.getState() == BUZ_OFF){
				buz.buzzStart();
			}
		}
	}
	else if(pin == btn2.getPin()){
		if (HAL_GPIO_ReadPin(btn2.getGpio(), btn2.getPin()) == 0) {
			printf("DHT button\r\n");
			dht.DHT_main();
		}
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

void LedTask()
{
//	 TODO ------------------------------------------------------
	while(1)
	{
		if(dht.getTemp() < (double)Thresholds.getWarning()){
			bluLed.LedOn();
			redLed.LedOFF();
			buz.buzzStop();
		}
		else {
			bluLed.LedOFF();
			if(dht.getTemp() < (double)Thresholds.getCritical() ){
				redLed.LedOn();
				buz.buzzStart();
			}
			else{
				redLed.LedBlink();
				buz.buzzStart();
			}
		}
		osDelay(1000);
	}
}







