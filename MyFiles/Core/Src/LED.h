/*
 * LED.h
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */

#ifndef SRC_LED_H_
#define SRC_LED_H_
#include <stdint.h>
#include "main.h"

typedef enum _ledState
{
	LED_OFF,
	LED_ON,
	LED_BLINK,
} LED_STATE;


typedef struct _led
{
	LED_STATE state;
	int counter;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int period;
}LED;


void ledInit(LED* led, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void ledOn(LED* led);
void ledOff(LED* led);
void ledBlink(LED* led, int period);
void ledOnTimerInterrupt(LED* led);
void ledOnPeriodTask(LED* led);
void ledStart(LED* led);
//void TIMER_CALLBACK()
//{
//	ledOnTimerInterrupt(&ledR);
//	ledOnTimerInterrupt(&ledG);
//}


#endif /* SRC_LED_H_ */

///* Private user code ---------------------------------------------------------*/
///* USER CODE BEGIN 0 */
////FlashLightState state
//
////#define SW1_Pin GPIO_PIN_10
////#define SW1_GPIO_Port GPIOA
//
//
//void HAL_GPIO_EXTI_Callback(uint16_t pin)
//{
//	//int i=0;
//	static uint32_t press, release;
//
//	if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == 0) {
//		press = HAL_GetTick();
//	}
//	else {
//		release = HAL_GetTick();
//		if(( release - press) > 500){
//			HAL_UART_Transmit( &huart2 , (uint8_t*) "long press\r\n" , 14 , 100);
//		}
//		else{
//			HAL_UART_Transmit( &huart2 , (uint8_t*) "short press\r\n" , 15 , 100);
//		}
//	}
//
//}
//
//extern int bright_set;
//LED ledR;
//LED ledB;
//
//RGB rgb1;
//RGB rgb2;
//RGB rgb3;
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * tim)
//{
//	ledOnTimerInterrupt(&ledB);
//	ledOnTimerInterrupt(&ledR);
//
//	rgbOnTimerInterrupt(&rgb1);
//	rgbOnTimerInterrupt(&rgb2);
//	rgbOnTimerInterrupt(&rgb3);
//
//}
