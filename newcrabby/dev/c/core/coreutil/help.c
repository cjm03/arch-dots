#include <stdio.h>

int linecount(const char* filename) {
    FILE* f;
    char ch;
    int lines = 0;

    f = fopen(filename, "r");
    if (!f) return -1;

    while ((ch = fgetc(f)) != EOF) {

        if (ch == '\n') lines++;

    }

    fclose(f);
    return lines;
}
