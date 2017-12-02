
#ifndef SERVER_FUNCTIONS_H_INCLUDED
#define SERVER_FUNCTIONS_H_INCLUDED







void sendBalance(int sockfd, Client_t *client);

Client_t* Authenticate(int sockfd, Client_t *head);
void sendClientData(int sockfd, Client_t *client);

#endif
