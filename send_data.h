
#ifndef SEND_DATA_H_INCLUDED
#define SEND_DATA_H_INCLUDED

#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <stdint.h>

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

void send_int(int sock_fd, int value);
int recv_int(int sock_fd);
void send_char(int sock_fd, char *data);
void recv_char (int sockfd, char* data);
void send_double(int sock_fd, double value);
double recv_double(int sock_fd);

#endif
