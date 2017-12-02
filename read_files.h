#ifndef READ_FILES_H_INCLUDED
#define READ_FILES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

#define BUFFER_SIZE 255
#define NUM_OF_ACCS 3
#define AccountFile "Accounts.txt"
#define AuthenticationFile "Authentication.txt"
#define ClientDetailsFile "Client_Details.txt"
#define TransactionFile "Transactions.txt"


typedef struct LoanAcc {
	int accountNumber;
	double openingBalance, closingBalance;

} LoanAcc_t;

typedef struct SavingsAcc {
	int accountNumber;
	double openingBalance, closingBalance;
} SavingsAcc_t;

typedef struct CreditAcc {
	int accountNumber;
	double openingBalance, closingBalance;
} CreditAcc_t;

typedef struct Client {
	int client_num, pin;
	int number, accountNumbers[NUM_OF_ACCS];
	char username[BUFFER_SIZE], fName[BUFFER_SIZE], lName[BUFFER_SIZE];
	LoanAcc_t *loan; 
	SavingsAcc_t *savings;
	CreditAcc_t *credit; 
 	struct Client *next;

} Client_t;

Client_t* FindClientAuthenticate(username, password);

Client_t* GenerateClientList();
Client_t* FindClientNum(Client_t *head, int client_num);
int findAccountType(int accountNumber);
void InsertClientDetails(Client_t *head);
Client_t* findAccountNum(Client_t *head, int accountNum);
void InsertAccountBalance(Client_t *head);
void destroyList(Client_t *head);
double findAccountBalance(Client_t *client, int accountNum);

#endif
