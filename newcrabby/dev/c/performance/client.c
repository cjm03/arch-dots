#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(void)
{
    int cliSock;
    char str[255];
    struct sockaddr_in cliAddr;
    socklen_t addrsize;
    cliSock = socket(AF_INET, SOCK_STREAM, 0);
    cliAddr.sin_family = AF_INET;
    cliAddr.sin_port = htons(2000);
    cliAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(cliAddr.sin_zero, '\0', sizeof(cliAddr.sin_zero));
    addrsize = sizeof(cliAddr);
    int con = connect(cliSock, (struct sockaddr*)&cliAddr, addrsize);
    recv(cliSock, str, 255, 0);
    printf("Data: %s\n", str);
    return 0;
}
