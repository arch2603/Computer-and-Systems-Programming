#include <stdio.h>
#include <stdlib.h>


#ifndef LOGGINSCREEN_H_INCLUDED
#define LOGGINSCREEN_H_INCLUDED

unsigned int client_number;
char client_name[20];
int loggin_screen(unsigned int * cl_num, char *user_name, char *password);

#endif // LOGGINSCREEN_H_INCLUDED
