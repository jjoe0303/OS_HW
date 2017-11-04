#ifndef SERVER_H
#define SERVER_H

#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>
#include <pthread.h>

//void cleanValue(char value[]);
void getPid(char pid[],char inputBuffer[]);
void scanString(char buffer[],char value[]);
void getCmdline(FILE *fin,char value[]);
void openFile(FILE *fin,char pid[],char buffer[],char work,char value[]);
void listAll(char base[]);
void *pthread_handler(void *);


#endif
