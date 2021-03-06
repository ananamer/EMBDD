/*
 * Cli.c
 *
 *  Created on: 17 Jul 2022
 *      Author: student
 */

#include "Cli.h"
#include "CommTask.h"
#include "main.h"
#include "Button.h"
#include "LED.h"
#include "BUZ.h"
#include "DHT.h"
#include <stdlib.h>

extern LED ledB;
extern LED ledR;
extern BUZ buz;
extern DHT _dht;

static void ledOnCmd(void * obj, char * param)
{
	(void)param;
	LED * led = (LED *)obj;
	ledOn(led);
}
static void ledOffCmd(void * obj, char * param)
{
	(void)param;
	LED * led = (LED *)obj;
	ledOff(led);
}
static void ledBlinkCmd(void * obj, char * param)
{
	int period = 300;

	LED * led = (LED *)obj;
	if (param != NULL) {
		period = atoi(param);
	}

	ledBlink(led, period);
}

static void playCmd(void * obj, char * param)
{
	(void)param;

	BUZ * buzzer = (BUZ *)obj;
	buzzerStart(buzzer);
}
static void pauseCmd(void * obj, char * param)
{
	(void)param;

	BUZ * buzzer = (BUZ *)obj;
	buzzerStop(buzzer);
}

static void helpCmd(void * obj, char * param)
{
	(void)obj;
	(void)param;
	printCommands();
}
static void tmpCmd(void * obj, char * param)
{
	(void)param;
	DHT * dht = (DHT *)obj;
	//	DHT_main();
	DHT_main_Async(dht);
}
void cliInit()
{
	registerCommand("blueon", ledOnCmd, &ledB);
	registerCommand("redon", ledOnCmd, &ledR);
	registerCommand("blueblink", ledBlinkCmd, &ledB);
	registerCommand("redblink", ledBlinkCmd, &ledR);
	registerCommand("blueoff", ledOffCmd, &ledB);
	registerCommand("redoff", ledOffCmd, &ledR);


	registerCommand("play", playCmd, &buz);
	registerCommand("pause", pauseCmd, &buz);
	registerCommand("tone", playToneCmd, &buz);


	registerCommand("help", helpCmd, NULL);
	registerCommand("temp", tmpCmd, &_dht);

}
