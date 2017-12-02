/*
 * interface.h
 *
 *  Created on: 30/09/2016
 *      Author: archie
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>



#ifndef INTERFACE_H_
#define INTERFACE_H_

enum selection{

    account_bal,
    withdraw,
    deposit,
    transfer,
    transaction_list,
    signout
};

char client_uname[20];

void General_account_menu();
double Withdrawal();
void _Deposit(double d_fund);

int account_Type_Mainmenu(unsigned int client_number, char cl_name[], enum selection sel, int);
int loggin_screen();


//can put global variables here between ifndef and endif
//can also put function prototypes



#endif /* INTERFACE_H_ */
