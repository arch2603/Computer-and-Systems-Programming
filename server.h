
#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED


#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 255
#include "logginscreen.h"

void client_exit(int sockfd);

#endif
