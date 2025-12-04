#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFERSIZE 255

int main(void)
{
    int fr;
    char str[BUFFERSIZE];
    fr = open("FIFOPipe", O_RDONLY);
    read(fr, str, BUFFERSIZE);
    printf("Read from FIFO pipe: %s\n", str);
    close(fr);
    return 0;
}
