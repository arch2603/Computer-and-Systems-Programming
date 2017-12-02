#include "server.h"
#include "send_data.h"
#include "read_files.h"
#include "server_functions.h"

//#include "interface.h"

void listening(int * sock_des)
{
	listen(*sock_des, 5);
}


void client_exit(int sockfd) {
	close(sockfd);
}

void handle_connection(int new_sock_fd, Client_t *head) {
	char selectedoption[BUFFER_SIZE];
	Client_t *valid = Authenticate(new_sock_fd, head);	
	int accountNumber;
	double balance;
	char buffer[20];
	if(valid == NULL) {
		send_int(new_sock_fd, 0);
		client_exit(new_sock_fd);
	} else {
		/*transfer data over to user
		  */
		send_int(new_sock_fd, 1);
			
		sendClientData(new_sock_fd, valid);
		while(1) {
			recv_char(new_sock_fd, selectedoption);
			if(strcmp(selectedoption, "BALANCE")) {
				printf("Client has requested to see account balance\n");
				sendBalance(new_sock_fd, valid);
			} else if (strcmp(selectedoption, "WITHDRAWAL")) {
				printf("Client has selected WITHDRAWAL\n");
			}
			selectedoption[0] = '\0';
			bzero(selectedoption, BUFFER_SIZE);
			printf("Done! Waiting for new input from client\n");

		}

	}
}


void accept_connection(Client_t *head, int* new_sock_fd, int *old_sock_fd, struct sockaddr_in cli_addr, int cli_len)
{
	int true = 1;

	while(true)
	{
		*new_sock_fd = accept(*old_sock_fd,(struct sockaddr *)&cli_addr, &cli_len);

		if(*new_sock_fd < 0)
		{
			perror("Error in accepting the connection");
			exit(1);
		}

		handle_connection(*new_sock_fd, head);
		
		

	}

}


int main(int argc, char *in_con[])
{
	int sock_descriptor, new_socket_fd, portnum, cl_len, _listen;
	Client_t *head = GenerateClientList();
	InsertClientDetails(head);
	InsertAccountBalance(head);
 
	struct sockaddr_in server_addr, client_addr;
	

	sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	//Check that the socket was successfully created
	if(sock_descriptor < 0)
	{
		perror("Error opening socket");
		exit(1);
	}

	//Initializing socket structure
	bzero((char *) &server_addr, sizeof(server_addr));
	portnum = 5717; //assigning port number use for communication

	server_addr.sin_family = AF_UNSPEC;
	//listening to any Internet interface on the server
	server_addr.sin_port = htons(portnum);//converting decimal number into byte in a specific order
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//Any adddress from the internet

	//Binding the host address i.e. port number of the host machine
	if(bind(sock_descriptor, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Error on binding");
		exit(1);
	}

	//listening to multiple host or client connections
	listening(&sock_descriptor);
	cl_len = sizeof(client_addr);

	accept_connection(head, &new_socket_fd, &sock_descriptor, client_addr, cl_len);

	return 0;
}




