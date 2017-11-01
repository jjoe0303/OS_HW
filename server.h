#ifndef SERVER_H
#define SERVER_H

#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

void openFile(FILE *fin,char pid[],char buffer[]);
#endif
