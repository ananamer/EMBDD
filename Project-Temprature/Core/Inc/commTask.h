/*
 * commTask.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_COMMTASK_H_
#define SRC_COMMTASK_H_
#include "CliCommand.h"

#define MAX_COMMANDS 50

typedef void (*HanlderFunc)(void *, char *);

int commTask();
void handleCommand();
//int _write(int fd, char* ptr, int len);
void registerCommand(const char * name, CliCommand * command);
void printCommands();

#endif /* SRC_COMMTASK_H_ */
