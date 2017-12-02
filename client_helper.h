
#ifndef CLIENT_HELPER_H_INCLUDED
#define CLIENT_HELPER_H_INCLUDED
#define BUFFER_SIZE 255
#include "send_data.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <math.h>

typedef struct Client {
	char fName[BUFFER_SIZE], lName[BUFFER_SIZE];
	int client_num, savingsaccnum, loanaccnum, creditaccnum;
} Client_t;

//Client_t* getDataFromServer(int sockfd);

#endif
