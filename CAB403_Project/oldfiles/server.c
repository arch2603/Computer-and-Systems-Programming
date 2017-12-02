#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include "interface.h"

void listening(int * sock_des)
{
	listen(*sock_des, 5);
}

void accept_connection(int* new_sock_fd, int *old_sock_fd, struct sockaddr_in cli_addr, int cli_len)
{
	int true = 1;
	int pid;

	while(true)
	{
		*new_sock_fd = accept(*old_sock_fd,(struct sockaddr *)&cli_addr, &cli_len);

		if(*new_sock_fd < 0)
		{
			perror("Error in accepting the connection");
			exit(1);
		}

		//Creating a child porcess
		pid = fork();

		if(pid < 0)
		{
			perror("Error creating child process");
			exit(1);
		}

		if(pid == 0)
		{
			close(*old_sock_fd);
			read_input(new_sock_fd);
			exit(0);
		}else{

			close(*new_sock_fd);
		}

	}

}

void read_input(int * new_sock_fd){

	char buffer[256];
	int rd, new_so_fd;

	new_so_fd = *new_sock_fd;

	bzero(buffer,256);

	rd = read(*new_sock_fd,buffer,255);
	printf("Hello World, here is your message: %s\n", buffer);

	write_output(new_so_fd, &rd);
}

void write_output(int new_so_fd, int *rd)
{
	*rd = write(new_so_fd, "Message received, Good Bye", 18);
	if(*rd < 0){
		error("Error writing to socket");
	}
}

void server_side()
{
	int sock_descriptor, new_socket_fd, portnum, cl_len, _listen;
	char mem_buffer[256];

	struct sockaddr_in server_addr, client_addr;
	//struct addrinfo

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
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//

	//Binding the host address i.e. port number of the host machine
	if(bind(sock_descriptor, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Error on binding");
		exit(1);
	}

	//listening to multiple host or client connections
	listening(&sock_descriptor);
	cl_len = sizeof(client_addr);

	accept_connection(&new_socket_fd, &sock_descriptor, client_addr, cl_len);



	//sockaddr &serverAddrCast = (sockadd &) serverAddr;
}






