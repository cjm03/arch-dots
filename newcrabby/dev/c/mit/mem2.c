#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char* str = malloc(sizeof(char) * 32);
    memcpy(str, "hakuna matata!", strlen("hakuna matata!"));
    printf("%s\n", str);
    free(str);
}
