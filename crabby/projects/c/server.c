/*
 *  server.c
 *  Start the server.
*/

#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>

#include "server.h"

#define PORT 8080
#define BUFFER_SIZE 4096

//======================================
// start, bind, listen
//======================================

int serverStart(struct sockaddr_in* server_addr)
{

    int enable = 1;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        perror("setsockopt REUSEADDR");
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0) {
        perror("setsockopt REUSEPORT");
    }

    server_addr->sin_family = AF_INET;
    inet_pton(AF_INET, "0.0.0.0", &server_addr->sin_addr);
    server_addr->sin_port = htons(PORT);

    /* BIND */
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(*server_addr)) != 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    
    /* LISTEN */
    if (listen(server_fd, 10) != 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

//====================================
// accept
//====================================

int serverAccept(int server_fd)
{
    int client_fd = accept(server_fd, NULL, NULL);
    
    if (client_fd != -1) {
        return client_fd;
    } else {
        return -1;
    }
}







