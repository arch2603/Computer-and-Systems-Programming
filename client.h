
#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED



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
#include "client_helper.c"
#include "disp_menu.h"
#include "send_data.h"

#define BUFFER_SIZE 255
void client_Side(int portnum, char *hostname[]);

void exit_application(int sockfd);


#endif
