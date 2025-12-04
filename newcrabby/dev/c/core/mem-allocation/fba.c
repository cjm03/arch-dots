#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fba.h"

#define BUFFERN 1024

int main(void) {
    static uint8_t buffer[BUFFERN];

    fba_t fba = {};
    fbaInit(&fba, buffer, BUFFERN);

    int* v = fbaAllocOpt(&fba, sizeof(*v), _Alignof(*v));
    if (!v) {
        perror("fbaAllocOpt");
        return EXIT_FAILURE;
    }
    struct {
        int a;
        int b;
    } *s = fbaAllocOpt(&fba, sizeof(*s), _Alignof(*s));

    char* str = fbaAllocOpt(&fba, 32, _Alignof(char));

    fbaReset(&fba);
    return EXIT_SUCCESS;
}
