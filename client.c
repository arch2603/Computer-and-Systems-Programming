#include "client.h"

Client_t* getDataFromServer(int sockfd) {
	Client_t *client;
	recv_char(sockfd, client->fName);
	printf("First name = %s\n",client->fName );
	recv_char(sockfd, client->lName);
	printf("last name = %s\n",client->lName );
	client->client_num = recv_int(sockfd);
	printf("client num = %d\n",client->client_num );
	client->savingsaccnum = recv_int(sockfd);
	printf("saving acc = %d\n",client->savingsaccnum );
	client->loanaccnum = recv_int(sockfd);
	printf("loan acc = %d\n",client->loanaccnum );
	client->creditaccnum = recv_int(sockfd);
	printf("credit acc = %d\n",client->creditaccnum );
	return client;

}


int main(int argc, char * argv[])
{
	int portnumber;

	if(argc < 3)
	{

		fprintf(stderr, "usage %s hostname port\n", argv[0]);
	}
	
	portnumber = atoi(argv[2]);

	//opening the port socket, by setting up port number for
	//communication between client and server
	client_Side(portnumber, argv);

	return 0;
}


/*
 * Function: client_side
 * Parameters:
 * 		- integer : port number read from console
 * 		- char * : A pointer to  an array which is he hostname read from console
 * 	Description:
 * 		- This function establishes the connection between the client side with the server side. It setup, bind and then
 * 		  read and write between the client and the server.
 */
void client_Side(int portnum, char *hostname[])
{
	int sockfd; int valid =0;
	int selected_int = 0;
	struct hostent *server;
	struct sockaddr_in their_addr; /* connector's address information */
	Client_t *client;

	//check if host name is entered from console or standard-in
	if ((server = gethostbyname(hostname[1])) == NULL) {
		herror("gethostbyname");
		exit(1);
	}
	//count not opent the socket for communication
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error opening socket: ");
		exit(1);
	}


	their_addr.sin_family = AF_INET;      /* host byte order */
	their_addr.sin_port = htons(atoi(hostname[2]));    /* short, network byte order */
	their_addr.sin_addr = *((struct in_addr *)server->h_addr);
	bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */
									 

	//Client not successfully connected
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("unsuccessful connection ");
		exit(1);
	} 

	valid = display_Main_Menu(sockfd);
	int account_num;
	double balance = 0;
	double digit;
	int response;
	if(valid) {
		//Authentication successful
		printf("In client.c, getting data from server\n");
		client = getDataFromServer(sockfd);	

		while(1) {
			selected_int = enter_selection();
			
			switch(selected_int) {
				case 1:
					account_num = accountBalanceMenu(client);
					send_char(sockfd, "BALACE");
					send_int(sockfd, account_num);
					balance = recv_double(sockfd);
					if(account_num % 13 == 0) {
						balance = balance + 5000;
					}
					printf("\n\n Current balance for account %d: $%.2lf\n", account_num, balance);
					break;
				case 2:
					printf("Withdrawal\n");
					account_num = withdrawalAccountNum(client);
					printf("The selected account number is %d\n", account_num);
					digit = withdrawalAmount();
					send_double(sockfd, digit);
					response = recv_int(sockfd);
					if(response) {
						balance = recv_double(sockfd);
						printf("Withrdrawal completed: Closing balance: %.2lf \n", balance);
					} else {
						printf("Insufficient funds - Unable to process request\n");
					}

					break;
				case 3: 
					printf("Deposit\n");
					break;
				case 4: 
					printf("Transfer\n");
					break;
				case 5:
					printf("Transaction history\n");

				case 6:
					exit_application(sockfd);
					break;

			}
		}
	} else {
		printf("Username or password incorrect, closing connection \n");
		exit_application(sockfd);
	}
}

void exit_application(int sockfd) {
	close(sockfd);
}
