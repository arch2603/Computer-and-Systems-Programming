#include "client.h"

/*Function prototypes */
void client_Side(int portnum, char *hostname[]);

int display_Main_Menu(int sockfd);

//============================================================================================================//


void send_int(int new_sock_fd, int value) {
	int n;
	uint32_t netbits = htons(value);
	n = write(new_sock_fd, &netbits, sizeof(uint32_t));
	if (n < 0) error("ERROR reading from socket");    
}

int recv_int(int new_sock_fd) {
	uint32_t number_of_bytes, i=0;
	uint32_t statistics;

	if ((number_of_bytes=recv(new_sock_fd, &statistics, sizeof(uint32_t), 0)) == -1) {
		perror("recv");
		exit(1);
	}

	return ntohl(statistics);
}

/*
 * Function: send_Message
 * Parameters:
 * 		- integer : sockfd-socket filedescriptor
 * 		- char * data : Pointer to a char or string of char
 * 	Description:
 * 		- Send the user name and pin number to the server for authentication.
 */

void send_Message(int sockfd, char *data)
{
	int n;
	n = write(sockfd, data, strlen(data));
	if(n < 0) 
		error("ERROR WRITING TO SOCKET");
}

void recv_char (int sockfd, char* data) {
	int n;
	n = read(sockfd, data, 255);
	if (n < 0) {
		perror("ERROR reading from socket");
		exit(1);
	}
	
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
	int sockfd; int valid;
	struct hostent *server;
	struct sockaddr_in their_addr; /* connector's address information */

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
	printf("Line 118 VALID: %d", valid);

	// Start of login code


	/*printf("%s\n",buffer);
		int valid ;

		if(valid) {
			//Authentication successful
			printf("Valid login %d \n \n \n \n", valid);
		} else {
			printf("Username or password incorrect, closing connection \n");
			close(sockfd);
			break;
		}*/
}

int display_Main_Menu(int sockfd)
{
	char buffer[255];
	int valid; int count = 3;

	while(count > 0)
	{
		//printf("Please enter the message: ");
		printf("=======================================================\n");
		printf("\n");
		printf("\n");
		printf("Welcome to the Online ATM System\n");
		printf("\n");
		printf("\n");
		printf("=======================================================\n");
		printf("You are required to logon with your registered Username and PIN\n");

		char username[BUFFER_SIZE];
		char password[BUFFER_SIZE];

		//zerolising memory or buffer i.e. array used to store first name and last name
		bzero(username, BUFFER_SIZE);
		bzero(password, BUFFER_SIZE);

		//Requesting user/client user name and pin number and send to server for authentication
		printf("Please enter username--> ");
		fgets(username,255,stdin);
		send_Message(sockfd, username);
		printf("Please enter your password-->");
		fgets(password,255,stdin);
		send_Message(sockfd, password);

		bzero(buffer,256);

		valid = recv_int(sockfd);

		count--;
		printf("Line 174 Count is %d", count);

	}

	return valid;

}
