/*
 * commTask.c
 *
 *  Created on: 17 Jul 2022
 *      Author: student
 */
#include "main.h"
#include "commTask.h"
#include <string.h>
#include <stdio.h>

#define MAX_COMMANDS 20
#define MAX_BUFFER_LENGTH 100

extern UART_HandleTypeDef huart2;

typedef struct _reg_comm
{
	const char* name ;
	HanlderFunc func;
	void * obj;
}REG_COMM;

REG_COMM commandsArr[MAX_COMMANDS];
uint8_t cmdbuffer[MAX_BUFFER_LENGTH];

static int commandsCount = 0;
static int cmdcount = 0;
static int cmdprint = 0;
//char first_word[MAX_BUFFER_LENGTH];


int _write(int fd, char* ptr, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t *) ptr, len, HAL_MAX_DELAY);
    return len;
}

void registerCommand(const char * name,HanlderFunc func, void * obj)
{
	if (commandsCount >= MAX_COMMANDS) {
			printf("Too many commands, cannot register\r\n");
			return;
		}

	commandsArr[commandsCount].name = name;
	commandsArr[commandsCount].func = func;
	commandsArr[commandsCount].obj = obj;
	commandsCount++;
}

int commTask()
{
	uint8_t ch;

	HAL_StatusTypeDef Status = HAL_UART_Receive(&huart2, &ch, 1, 10);
	if (Status != HAL_OK)
	{
		if ((huart2.Instance->ISR & USART_ISR_ORE) != 0)
		{
			__HAL_UART_CLEAR_OREFLAG(&huart2);
		}

		// here we have a time to print the command
		while (cmdprint < cmdcount)
		{
			HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
		}

		return 0;
	}

	if (ch == '\r' || ch == '\n')
	{
		// here we have a time to print the command
		while (cmdprint < cmdcount)
		{
			HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
		}

		HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 0xFFFF);

		cmdbuffer[cmdcount] = 0;
		cmdcount = 0;
		cmdprint = 0;

		// command is ready
		return 1;
	}
	else if (ch == '\b')
	{
		char bs[] = "\b \b";
		cmdcount--;
		cmdprint--;
		HAL_UART_Transmit(&huart2, (uint8_t*)bs, strlen(bs), 0xFFFF);
	}
	else
	{
		if (cmdcount >= MAX_BUFFER_LENGTH)
		{
			cmdcount = 0;
			cmdprint = 0;
		}

		cmdbuffer[cmdcount++] = ch;
	}

	return 0;
}

void handleCommand()
{
	char * param = NULL;

	// find space to split a command to a command name and parameters
	char * delimPtr = strchr((const char*)cmdbuffer, ' ');
	if (delimPtr != NULL) {
		// put null character to split command name and parameters
		*delimPtr = '\0';
		param = delimPtr + 1;
		// find first non space character - it's parameters beginning
		while (*param && *param == ' ') {
			param++;
		}
		if (*param == '\0') {
			param = NULL;
		}
	}

	for (int i = 0; i < commandsCount; i++) {
		if (strcmp(commandsArr[i].name, (char *)cmdbuffer) == 0) {
			commandsArr[i].func(commandsArr[i].obj, param);
			return;
		}
	}

	printf("Invalid command\r\n");

}

void printCommands()
{
	printf("Available commands:\r\n");
	for (int i = 0; i < commandsCount; i++) {
		printf("\t%s\r\n", commandsArr[i].name);
	}
}































