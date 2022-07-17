/*
 * commTask.h
 *
 *  Created on: 17 Jul 2022
 *      Author: student
 */

#ifndef SRC_COMMTASK_H_
#define SRC_COMMTASK_H_

typedef void (*HanlderFunc)(void *, char *);

int commTask();
void handleCommand();
int _write(int fd, char* ptr, int len);
void registerCommand(const char * name,HanlderFunc func, void * obj);
void printCommands();

#endif /* SRC_COMMTASK_H_ */
