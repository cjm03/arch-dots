#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#define PORT 8080
#define BUFFER_SIZE 4096

/* start server, bind and listen */
int serverStart(struct sockaddr_in* server_addr);

/* accept */
int serverAccept(int server_fd);

#endif // SERVER_H
