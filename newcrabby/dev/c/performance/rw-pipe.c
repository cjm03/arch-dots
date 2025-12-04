#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define max 50

int main(void)
{
    char str[max];
    int pp[2];

    if (pipe(pp) < 0) {
        exit(1);
    }
    printf("Enter first message to write to pipe: ");
    // scanf("%s ", str);
    fgets(str, max, stdin);
    write(pp[1], str, max);
    printf("Enter second message: ");
    // scanf("%s", str);
    fgets(str, max, stdin);
    write(pp[1], str, max);
    printf("Messages from pipe:\n");
    read(pp[0], str, max);
    printf("%s\n", str);
    read(pp[0], str, max);
    printf("%s\n", str);
    return 0;
}
