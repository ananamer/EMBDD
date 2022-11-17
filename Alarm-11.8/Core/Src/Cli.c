/*
 * Cli.c
 *
 *  Created on: 17 Jul 2022
 *      Author: student
 */

#include "Cli.h"
#include "CommTask.h"
#include "main.h"
#include "AlarmManager.h"
#include "Alarm.h"
#include <stdio.h>

static void helpCmd(void * obj, char * param)
{
	(void)obj;
	(void)param;
	printCommands();
}

static void setCmd(void * obj, char * param)
{
	(void)obj;

	ALARM  alarm;
	DateTime time;

	char name[nameSize];
	//   setAlarm name hh:mm:ss DD/MM/YY
	int paramsNum = sscanf(param, "%s %d:%d:%d %d/%d/%d", name, &(time.hours),&(time.min) , &(time.sec),
														  &(time.day), &(time.month), &(time.year) );
//	printf("#####\r\n");
	printf("%s %d:%d:%d %d/%d/%d\r\n", name, time.hours, time.min , time.sec,  time.day, time.month, time.year);
	// setAlarm wakeup 13:12:11 11/11/22
	if(paramsNum != 7){
		printf("Error in set time and date\r\n");
		return;
	}
	createAlarm(&time, name);
}




static void deleteCmd(void * obj, char * param)
{
	(void)obj;
	(void)param;
	//
}
static void editCmd(void * obj, char * param)
{
	(void)obj;
	(void)param;
	//
}
static void printCmd(void * obj, char * param)
{
	(void)obj;
	(void)param;
	printAlarms();
	//
}
void cliInit()
{
	registerCommand("help", helpCmd, NULL);
	registerCommand("setAlarm", setCmd, NULL);
	registerCommand("deleteAlarm", deleteCmd, NULL);
	registerCommand("editAlarm", editCmd, NULL);
	registerCommand("printAlarms", printCmd, NULL);
}
