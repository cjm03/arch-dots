/*
 *  server.c - The Server.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/file.h>
#include <fcntl.h>

#define PORT "8080"

#define SERVER_CLIPS "/data/mp4/clips1"

int sendResponse(int fd, char* header, char* content_type, void* body, int content_length)
{
    const int max_response_size = 262144;
    char response[max_response_size];

    //////////////////
    // Implement Me //
    //////////////////
    size_t response_length = strlen(response);

    int rv = send(fd, response, response_length, 0);

    if (rv < 0) {
        perror("send");
    }
    return rv;
}

int main(void)
{
    int newfd;
    struct sockaddr_storage their_addr;
    char s[INET6_ADDRSTRLEN];

    struct cache* cache = createCache(10, 0);

    int listenfd = getListenerSocket(PORT);

    if (listenfd < 0) {
        fprintf(stderr, "webserver: fatal error getting listening socket\n");
        exit(1);
    }

    printf("webserver: waiting for connections on port %s...\n", PORT);

    while (1) {
        socklen_t sin_size = sizeof(their_addr);

        newfd = accept(listenfd, (struct sockaddr*)&their_addr, &sin_size);
        if (newfd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family, getInAddr((struct sockaddr*)&their_addr), s, sizeof(s));
        printf("server: got connection from %s\n", s);

    // handleRequest(newfd, cache);

        close(newfd);
    }
    return 0;
}
