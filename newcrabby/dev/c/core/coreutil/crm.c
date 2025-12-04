#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "help.h"


int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "rm: no target specified\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++) {
        if (unlink(argv[i]) != 0) {
            fprintf(stderr, "rm: unable to remove file '%s'\n%s\n", argv[i], strerror(errno));
        }
    }
    return 0;
}
