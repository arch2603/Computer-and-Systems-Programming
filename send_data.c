#include "send_data.h"

void send_int(int sock_fd, int value) {
	uint32_t statistics;  
	statistics = htonl(value);
	send(sock_fd, &statistics, sizeof(uint32_t), 0);

}

void send_double(int sock_fd, double value) {
	double statistics;  
	//statistics = htonl(value);
	send(sock_fd, &value, sizeof(value), 0);

}

int recv_int(int sock_fd) {
	uint32_t number_of_bytes;
	uint32_t statistics;

	if ((number_of_bytes=recv(sock_fd, &statistics, sizeof(uint32_t), 0)) == -1) {
		perror("recv");
		exit(1);
	}

	return ntohl(statistics);
}

double recv_double(int sock_fd) {
	uint32_t number_of_bytes;
	double statistics;

	if ((number_of_bytes=recv(sock_fd, &statistics, sizeof(statistics), 0)) == -1) {
		perror("recv");
		exit(1);
	}

	return statistics; //ntohl(statistics);
}


void send_char(int sock_fd, char *data) {
	int n;
	send_int(sock_fd, strlen(data));
	n = write(sock_fd, data, strlen(data));
	
	if(n < 0) 
		perror("ERROR WRITING TO SOCKET");
}

void recv_char (int sockfd, char* data) {
	int n, length;
	length = recv_int(sockfd);
	n = read(sockfd, data, length );
	if (n < 0) {
		perror("ERROR reading from socket");
		exit(1);
	}
	data[n] = '\0';
	
}
