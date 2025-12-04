#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "help.h"


void ls(const char* path) {
    DIR* d = opendir(path);
    if (d == NULL) {
        fprintf(stderr, "ls: unable to open directory '%s'\n%s\n", path, strerror(errno));
        return;
    }
    errno = 0;
    struct dirent* ent;
    while ((ent = readdir(d)) != NULL) {
        printf("%s\n", ent->d_name);
    }
    if (errno != 0) {
        fprintf(stderr, "ls: error occurred\n%s\n", strerror(errno));
    }
    closedir(d);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        ls(".");
        return EXIT_SUCCESS;
    } else if (argc < 3) {
        ls(argv[1]);
        return EXIT_SUCCESS;
    }
    fprintf(stderr, "ls: invalid use\n");
    return 0;
}
