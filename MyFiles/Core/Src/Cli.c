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
#include "RGB.h"
#include <stdlib.h>
#include "MainTimer.h"
#include "Clock.h"

extern LED ledB;
extern LED ledR;
extern BUZ buz;
extern DHT _dht;
extern CLOCK clk;
extern RGB rgb1, rgb2, rgb3;
// LED
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

// RGB
static void rgbOnCmd(void * obj, char * param)
{
	(void)param;
	RGB * rgb = (RGB *)obj;
	rgbOn(rgb);
}
static void rgbOffCmd(void * obj, char * param)
{
	(void)param;
	RGB * rgb = (RGB *)obj;
	rgbOff(rgb);
}
static void rgbblinkCmd(void * obj, char * param)
{
//	(int)param;
	RGB * rgb = (RGB *)obj;
	rgbBlink(rgb, 300);
}

// Buzzer
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

// DHT
static void tmpCmd(void * obj, char * param)
{
	(void)param;
	DHT * dht = (DHT *)obj;
	//	DHT_main();
	DHT_main_Async(dht);
}

// Clock
static void clockStartCmd(void * obj, char * param)
{
	(void)param;
	CLOCK * clk = (CLOCK *)obj;
	clkOn(clk);
//	clkOff(CLOCK* clk);
}
static void clockStopCmd(void * obj, char * param)
{
	(void)param;
	CLOCK * clk = (CLOCK *)obj;
	clkOff(clk);

}

static void helpCmd(void * obj, char * param)
{
	(void)obj;
	(void)param;
	printCommands();
}

void cliInit()
{
	registerCommand("blueon", ledOnCmd, &ledB);
	registerCommand("redon", ledOnCmd, &ledR);
	registerCommand("blueblink", ledBlinkCmd, &ledB);
	registerCommand("redblink", ledBlinkCmd, &ledR);
	registerCommand("blueoff", ledOffCmd, &ledB);
	registerCommand("redoff", ledOffCmd, &ledR);

	registerCommand("rgb1on", rgbOnCmd, &rgb1);
	registerCommand("rgb2on", rgbOnCmd, &rgb2);
	registerCommand("rgb3on", rgbOnCmd, &rgb3);
	registerCommand("rgb1off", rgbOffCmd, &rgb1);
	registerCommand("rgb2off", rgbOffCmd, &rgb2);
	registerCommand("rgb3off", rgbOffCmd, &rgb3);

	registerCommand("rgb1blink", rgbblinkCmd, &rgb1);
	registerCommand("rgb2blink", rgbblinkCmd, &rgb2);
	registerCommand("rgb3blink", rgbblinkCmd, &rgb3);


	registerCommand("pause", pauseCmd, &buz);
	registerCommand("tone", playToneCmd, &buz);


	registerCommand("help", helpCmd, NULL);
	registerCommand("temp", tmpCmd, &_dht);

	registerCommand("clockon", clockStartCmd, &clk);
	registerCommand("clockoff", clockStopCmd, &clk);

}
