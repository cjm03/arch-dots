#ifndef NET_H
#define NET_H

void* getInAddr(struct sockaddr* sa);
int getListenerSocket(char* port);

#endif
