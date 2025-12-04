#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(void)
{
    int servSock, toSend;
    char str[255];
    struct sockaddr_in servAddr;
    servSock = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(2000);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));
    if (bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) != 0) {
        printf("Bind fail\n");
        return -1;
    }
    if (listen(servSock, 5) == -1) {
        printf("Listen fail\n");
        return -1;
    }
    printf("Text for client: ");
    fgets(str, 255, stdin);
    toSend = accept(servSock, (struct sockaddr*) NULL, NULL);
    send(toSend, str, strlen(str), 0);
    return 0;
}
