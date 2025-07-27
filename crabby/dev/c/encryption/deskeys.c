#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "des.h"

static FILE *key_file, *input_file, *output_file;

int main(int argc, char* argv[])
{
    clock_t start, finish;
    double time_taken;
    unsigned long file_size;
    unsigned short int padding;

    if (argc < 2) {
        printf("1 parameter required to specify action\n");
        return 1;
    }

    if (strcmp(argv[1], ACTION_GENKEY) == 0) {
        if (argc != 3) {
            printf("Invalid param count\n");
            return 1;
        }

        key_file = fopen(argv[2], "wb");
        if (!key_file) {
            printf("error opening file to write key to\n");
            return 1;
        }

        unsigned int iseed = (unsigned int)time(NULL);
        srand(iseed);

        short int bytes_written;
        unsigned char* des_key = (unsigned char*)malloc(8 * sizeof(char));
        generateKey(des_key);
        bytes_written = fwrite(des_key, 1, DESKEYSIZE, key_file);
        if (bytes_written != DESKEYSIZE) {
            printf("error writing key\n");
            fclose(key_file);
            free(des_key);
            return 1;
        }
        free(des_key);
        fclose(key_file);
    }

    return 0;
}
