/*
 * commTask.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "commTask.h"
#include <string.h>
#include <stdio.h>
#include "CliCommand.h"
#include "CLI.h"
#include "main.h"


#define MAX_BUFFER_LENGTH 100


extern UART_HandleTypeDef huart2;
uint8_t cmdbuffer[MAX_BUFFER_LENGTH];

int cmdcount = 0;
int cmdprint = 0;
char first_word[MAX_BUFFER_LENGTH];
CLI cli;

void commTask()
{
	printf("CommTask\r\n");
	while(1){
		if(communication()){
			handleCommand();
		}
	}
}
int communication()
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

	if (ch != '\r' && ch != '\n')
	{
		if (cmdcount >= MAX_BUFFER_LENGTH)
		{
			cmdcount = 0;
			cmdprint = 0;
		}
		cmdbuffer[cmdcount++] = ch;
		return 0;
	}
	// here we have a time to print the command
	while (cmdprint < cmdcount)
	{
		HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 0xFFFF);
	cmdbuffer[cmdcount] = 0;
	cmdcount = 0;
	cmdprint = 0;
	return 1;
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
	cli.performCommand((char *)cmdbuffer, param);



}

