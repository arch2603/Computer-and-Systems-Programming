#include "read_files.h"

Client_t* GenerateClientList() {
	FILE *authfile;
	
	Client_t *head = NULL, *current = NULL; 
	head = malloc(sizeof(Client_t));
	head->next = NULL;
	head->loan = NULL;
	head->savings = NULL;
	head->credit = NULL;
	int i;
	for(i = 0; i < NUM_OF_ACCS; i++) {
		head->accountNumbers[i] = 0;
	}
	current = head;
	

	authfile = fopen(AuthenticationFile, "r");
	if (authfile == NULL) {
		printf("File %s could not be found \n", AuthenticationFile);
		exit(EXIT_FAILURE);
	}
	char trash1[20], trash2[20], trash3[20];
	//Removing first line of headings
	fscanf(authfile, "%s %s %s", trash1, trash2, trash3);



	while(fscanf(authfile, "%s %d %d", current->username, &(current->pin), &(current->client_num)) != EOF) {
		current->next = malloc(sizeof(Client_t));
		current = current->next;
		current->next = NULL;
		current->loan = NULL;
		current->savings = NULL;
		current->credit = NULL;
		for(i = 0; i < NUM_OF_ACCS; i++) {
			current->accountNumbers[i] = 0;
		}


	}
	fclose(authfile);

	return head;

}

Client_t* FindClientNum(Client_t *head, int client_num) {
	Client_t *current = head;
	while(current->next != NULL) {
		if(client_num == current->client_num) {
			return current;
		} else {
			current = current->next;
		}
	}
	return NULL;
}

/* returns 1 if savings acc
   returns 2 if loan acc
   returns 3 if credit acc
   */
int findAccountType(int accountNumber) {
	
	if(accountNumber % 11 == 0)
		return 1;
	else if (accountNumber % 12 == 0)
		return 2;
	else 
		return 3;
}

void destroyList(Client_t *head) {
	Client_t *temp;

	while(head != NULL) {
		temp = head;
		head = head->next;
		if(temp->savings != NULL) {
			free(temp->savings);
		}
		if(temp->loan != NULL) {
			free(temp->loan);
		}
		if(temp->credit != NULL) {
			free(temp->loan);
		}
		free(temp);
	}
}

void InsertClientDetails(Client_t *head) {
	FILE *clientdetails;
	char fName[BUFFER_SIZE], lName[BUFFER_SIZE], accounts[BUFFER_SIZE];
	char *ptracct;
	int accountType, client_num, i, accountNumber;
	Client_t *current;
	
	clientdetails = fopen(ClientDetailsFile, "r");

	//removing the first line of the file
	char trash1[20], trash2[20], trash3[20], trash4[20];
	fscanf(clientdetails, "%s %s %s %s", trash1, trash2, trash3, trash4);
	
	while(fscanf(clientdetails, "%s %s %d %s",fName, lName, &client_num, accounts) != EOF) {
		current = FindClientNum(head, client_num);
		strcpy(current->fName, fName);
		strcpy(current->lName, lName);
		ptracct = strtok(accounts,",");
		while(ptracct != NULL) {

			accountNumber = atoi(ptracct);

			accountType = findAccountType(accountNumber);
			if(accountType == 1) {
				current->savings = malloc(sizeof(SavingsAcc_t));
				current->savings->accountNumber = accountNumber;
			} else if(accountType == 2) {
				current->loan = malloc(sizeof(LoanAcc_t));
				current->loan->accountNumber = accountNumber;
			} else {
				current->credit = malloc(sizeof(CreditAcc_t));
				current->credit->accountNumber = accountNumber;
			}
			
			for(i = 0; i < NUM_OF_ACCS; i++) {
				if(current->accountNumbers[i] == 0) {
					current->accountNumbers[i] = accountNumber;
					break;
				}
			}
			ptracct = strtok(NULL, ",");
		}
		

	}
	fclose(clientdetails);
}

Client_t* findAccountNum(Client_t *head, int accountNum) {
	Client_t *current = head;
	int i;
	while(current->next != NULL) {
		for(i = 0; i < NUM_OF_ACCS; i++) {
			if(current->accountNumbers[i] == accountNum) {
				return current;
			}
		}
	
		current = current->next;
	}
	return NULL;

}

double findAccountBalance(Client_t *client, int accountNum) {
	if(client->savings != NULL) {
		if(client->savings->accountNumber == accountNum) {	
			printf("savings card, balance is %lf\n", client->savings->closingBalance);
			return client->savings->closingBalance;
		}
	}
	if(client->loan != NULL) {
		if(client->loan->accountNumber == accountNum) {	
			printf("loan card, balance is %lf\n", client->loan->closingBalance);
			return client->loan->closingBalance;
		}
	}
	if (client->credit != NULL){ 
		printf("Credit card, balance is %lf\n", client->credit->closingBalance);
		return client->credit->closingBalance;
	}
	printf("account not found, exiting \n");
}


void InsertAccountBalance(Client_t *head) {
	Client_t *current;
	FILE *accounts;
	int accountNum, accountType;
	double openingbal, closingbal;

	accounts = fopen(AccountFile, "r");
	char trash1[20], trash2[20], trash3[20];
	fscanf(accounts, "%s %s %s", trash1, trash2, trash3);


	while(fscanf(accounts, "%d %lf %lf", &accountNum, &openingbal, &closingbal) != EOF) {
		current = findAccountNum(head, accountNum);
		accountType = findAccountType(accountNum);
		if(accountType == 1) {
			current->savings->openingBalance = openingbal;
			current->savings->closingBalance = closingbal;
		} else if (accountType == 2) {
			current->loan->openingBalance = openingbal;
			current->loan->closingBalance = closingbal;
		} else {
			current->credit->openingBalance = openingbal;
			current->credit->closingBalance = closingbal;
		}

	}
	fclose(accounts);

}


Client_t* FindClientAuthenticate(Client_t *head, char* username, int pin) {
	Client_t *current = head;
	printf("Attempting to traverse the list \n");
	int i = 0;
	for(; i < strlen(username); i++) {
		printf("%d ", username[i]);
	}
	printf("\n");
	//Traversing the list
	while(current->next != NULL) {
		printf("current username = %s and compare is %d\n", current->username, strcmp(current->username, username));
		if((strcmp(current->username, username) == 0) && (current->pin == pin)){
			printf("Client found\n");
			return current;
		}
		else {
			current = current->next;
		}
}
	printf("Client not found\n");
	return NULL;
}


/*int main() {
	Client_t *butterfly = NULL, *head = NULL;

	head = GenerateClientList();
	InsertClientDetails(head);
	butterfly = FindClientNum(head, 34457985);
	InsertAccountBalance(head);
	printf("%s %d %d %d %.2lf", butterfly->lName, butterfly->pin, butterfly->client_num, butterfly->savings->accountNumber, butterfly->savings->closingBalance);
	destroyList(head);
	return 0;
}*/










