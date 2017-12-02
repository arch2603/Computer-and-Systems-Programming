#include "disp_menu.h"

#define INPUT_SIZE 20


int enter_selection() {
	char input[INPUT_SIZE];
	int digit;
	printf("<1> Account balance\n");
	printf("<2> Withdrawal\n");
	printf("<3> Desposit\n");
	printf("<4> Transfer\n");
	printf("<5> Transaction Listing\n");
	printf("<6> Exit\n\n");

	do {
		printf("Selection option 1-6 -> ");
		bzero(input, INPUT_SIZE);
		fgets(input, INPUT_SIZE, stdin);
		digit = atoi(input);
		if(digit > 0 && digit < 7) {
			return digit;
		} else {
			printf("Invalid input\n");
		}
	} while(1);
}

int withdrawalAccountNum(Client_t *client) {
	int i = 1, digit;
	char input[INPUT_SIZE];
	int num_of_options = 0;
	int option[3];
	printf("\nSelect Account type\n");
	if(client->savingsaccnum != 0) {
		printf("%d. Savings account \n", i);
		option[i-1] = client->savingsaccnum; 
		num_of_options++; 
		i++;
	}
	if(client->creditaccnum!= 0) {
		printf("%d. Credit account \n", i);
		option[i-1] = client->loanaccnum; 
		num_of_options++; 
		i++; 
	}
	int j;
	do {
		printf("\n\n Select account type - ");
		bzero(input, INPUT_SIZE);
		fgets(input, INPUT_SIZE, stdin);
		digit = atoi(input);
		if(digit > 0 && digit <= num_of_options) {
			for(j = 0; j < num_of_options; j++) {
				printf("%d \n", option[j]);
			}
			printf("selcted option is %d and that belongs to accout %d\n", digit, option[digit-1]);
			return option[digit-1];
		} else {
			printf("Invalid input\n");
		}
	} while(1);
}

double withdrawalAmount() {
	double digit;
	char input[BUFFER_SIZE];
	do {
		printf("\n\nEnter the amount to withdraw -  ");
		bzero(input, INPUT_SIZE);
		fgets(input, INPUT_SIZE, stdin);
		digit = atof(input);
		if(digit < 0 ) {
			printf("Please input a number greater than 0 \n");
		} else {
			return digit;
		}

	} while(1);
}

int accountBalanceMenu(Client_t *client) {
	int i = 1, digit;
	char input[INPUT_SIZE];
	int num_of_options = 0;
	int option[3];
	printf("\nSelect Account type\n");
		if(client->savingsaccnum != 0) {
			printf("%d. Savings account \n", i);
			option[i-1] = client->savingsaccnum; 
			num_of_options++; 
			i++;
		}
		if(client->loanaccnum != 0) {
			printf("%d. Loan account \n", i);
			option[i-1] = client->loanaccnum; 
			num_of_options++; 
			i++; 
		} 
		if (client->creditaccnum != 0){
			printf("%d. Credit account \n", i);
			option[i-1] = client->creditaccnum; 
			num_of_options++; 
		}
	int j;
	do {
		printf("\n\n Select account type - ");
		bzero(input, INPUT_SIZE);
		fgets(input, INPUT_SIZE, stdin);
		digit = atoi(input);
		if(digit > 0 && digit <= num_of_options) {
			for(j = 0; j < num_of_options; j++) {
				printf("%d \n", option[j]);
			}
			printf("selcted option is %d and that belongs to accout %d\n", digit, option[digit-1]);
			return option[digit-1];
		} else {
			printf("Invalid input\n");
		}
	} while(1);
	
	
}


int display_Main_Menu(int sockfd)
{
	char username[BUFFER_SIZE];
	char password[BUFFER_SIZE];
	int valid = 0, pin;

	//printf("Please enter the message: ");
	printf("=======================================================\n");
	printf("\n");
	printf("\n");
	printf("Welcome to the Online ATM System\n");
	printf("\n");
	printf("\n");
	printf("=======================================================\n");
	printf("You are required to logon with your registered Username and PIN\n");


	//zerolising memory or buffer i.e. array used to store first name and last name
	bzero(username, BUFFER_SIZE);
	bzero(password, BUFFER_SIZE);

	//Requesting user/client user name and pin number and send to server for authentication
	printf("Please enter username--> ");
	fgets(username,BUFFER_SIZE,stdin);
	int size = strlen(username);
	username[size-1] = '\0';
	send_char(sockfd, username);
	printf("Please enter your password-->");
	fgets(password,BUFFER_SIZE,stdin);
	pin = atoi(password);
	send_int(sockfd, pin);


	valid = recv_int(sockfd);
	printf("Valid =%d\n", valid);

	return valid;

}
