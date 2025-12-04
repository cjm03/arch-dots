#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fw;
    char str[255];
    mkfifo("FIFOPipe", 0666);
    fw = open("FIFOPipe", O_WRONLY);
    printf("Enter text: ");
    fgets(str, 255, stdin);
    write(fw, str, sizeof(str));
    close(fw);
    return 0;
}
