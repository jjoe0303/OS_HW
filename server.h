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

void openFile(FILE *fin,char pid[],char buffer[]);
void listAll();

#endif
