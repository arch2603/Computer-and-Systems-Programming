#include "read_files.h"
#include "send_data.h"

Client_t* Authenticate(int sockfd, Client_t *head){
	char username[255];
	int pin;
	Client_t *valid;

	bzero(username,255);                                           
	recv_char(sockfd, username);
	pin = recv_int(sockfd);
	valid = FindClientAuthenticate(head, username, pin);
	return valid;
}

void sendBalance(int sockfd, Client_t *client) {
	int accountNum = recv_int(sockfd);
	double balance;
	balance = findAccountBalance(client, accountNum);
	printf("Balace is %lf\n", balance);
	send_double(sockfd, balance);
}

void handleWithdrawal(int sockfd, Client_t *client) {
	int accountNum = recv_int(sockfd);
	double withdrawalAmount = recv_double(sockfd);
	double balance;
	balance = findAccountBalance(client, accountNum);
	//Credit account, balance can go down to -5000
	if(findAccountType(accountNum) == 3 ) {
		if((balance - withdrawalAmount) < 5000) {
			//Withdrawel failed
			send_int(sockfd, 0);
		} else {
			client->credit->closingBalance = balance -withdrawalAmount;
			//Withdrawal successful
			send_int(sockfd, 1);
			send_double(sockfd, client->credit->closingBalance);
		}
	} else {
	//Savings account, balance can only go down to 0
		if((balance - withdrawalAmount) < 0) {
			//Withdrawel failed
			send_int(sockfd, 0);
		} else {
			client->savings->closingBalance = balance -withdrawalAmount;
			//Withdrawal successful
			send_int(sockfd, 1);
			send_double(sockfd, client->savings->closingBalance);
		}

	}
}

void sendClientData(int sockfd, Client_t *client) {
	send_char(sockfd, client->fName);
	send_char(sockfd, client->lName);
	send_int(sockfd, client->client_num);
	if(client->savings == NULL) {
		send_int(sockfd, 0);
	} else {
		send_int(sockfd, client->savings->accountNumber);
	}
	
	if(client->loan == NULL) {
		send_int(sockfd, 0);
	} else {
		send_int(sockfd, client->loan->accountNumber);
	}
	if(client->credit == NULL) {
		send_int(sockfd, 0);
	} else {
		send_int(sockfd, client->credit->accountNumber);
	}
}
