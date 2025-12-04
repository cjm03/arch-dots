#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "help.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file> \n", argv[0]);
        return 0;
    }

    FILE* f = NULL;
    long size = 0;
    char* buffer = NULL;
    int lines = 1;

    f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "cannot open file [%s]\n", argv[1]);
        return 0;
    }

    fseek(f, 0L, SEEK_END);
    size = ftell(f);
    rewind(f);

    buffer = (char*)malloc(size * sizeof(char));

    while ((fgets(buffer, size, f)) != NULL) {
        printf("%3d %s", lines, buffer);
        memset(buffer, 0, strlen(buffer) + 1);
        lines++;
    }

    lines = 0;
    free(buffer);
    fclose(f);

    lines = linecount(argv[1]);
    printf("CHARS: %ld LINES: %d\n", size, lines - 1);
    
    return 0;
}
