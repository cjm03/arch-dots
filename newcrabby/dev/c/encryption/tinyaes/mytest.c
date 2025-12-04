#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "aes.h"

char* portStrndup(char* buf, int n)
{
    char* p = malloc(n + 1);
    if (!p) return NULL;
    memcpy(p, buf, n);
    p[n] = '\0';
    return p;
}

int main(void)
{
    uint8_t key[] = {
        0x6F, 0x5F, 0x71, 0x67, 0x5A, 0x56, 0x65, 0x47,
        0x4C, 0x64, 0x4C, 0x4B, 0x23, 0x4C, 0x6F, 0x6F,
        0x35, 0x38, 0x79, 0x79, 0x7A, 0x79, 0x59, 0x53,
        0x52, 0x7A, 0x4A, 0x69, 0x36, 0x6C, 0x42, 0x75
    };
		
    char in[] = "OwVVJE-zgFrhW-f_AnC1-$_f#Be";
    char* in1 = portStrndup(in, strlen(in));
    unsigned char in2[] = "NL25E5hbb$ZEhJ6KKNxJaZG4@Knt$r0L";
    unsigned char in3[] = "e3BBEjMNr4oe5y@yzT0IjvZLGTg$ihIw";
    unsigned char in4[] = "XuXQQu-rYL6wq-6cwTwz-V6zi4K";
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);

    size_t insize = strlen(in);
    printf("Original: [%s]\n", in1);
    AES_ECB_encrypt(&ctx, (unsigned char*)in1);
    printf("\nECB encrypted: [");
    for (size_t i = 0; i < insize; i++) {
        printf("%c", in1[i]);
    }
    AES_ECB_decrypt(&ctx, (unsigned char*)in1);
    printf("]\n\nECB decrypted: [");
    for (size_t i = 0; i < insize; i++) {
        printf("%c", in1[i]);
    }
    printf("]\n\n");
    free(in1);
    // insize = sizeof(in2);
    // printf("Original: [%s]\n", in2);
    // AES_ECB_encrypt(&ctx, in2);
    // printf("\nECB encrypted: [");
    // for (size_t i = 0; i < insize; i++) {
    //     printf("%c", in2[i]);
    // }
    // AES_ECB_decrypt(&ctx, in2);
    // printf("]\n\nECB decrypted: [");
    // for (size_t i = 0; i < insize; i++) {
    //     printf("%c", in2[i]);
    // }
    // printf("]\n\n");
    //
    // insize = sizeof(in3);
    // printf("Original: [%s]\n", in3);
    // AES_ECB_encrypt(&ctx, in3);
    // printf("\nECB encrypted: [");
    // for (size_t i = 0; i < insize; i++) {
    //     printf("%c", in3[i]);
    // }
    // AES_ECB_decrypt(&ctx, in3);
    // printf("]\n\nECB decrypted: [");
    // for (size_t i = 0; i < insize; i++) {
    //     printf("%c", in3[i]);
    // }
    // printf("]\n\n");
    //
    // insize = sizeof(in4);
    // printf("Original: [%s]\n", in4);
    // AES_ECB_encrypt(&ctx, in4);
    // printf("ECB encrypted: [");
    // for (size_t i = 0; i < insize; i++) {
    //     printf("%c", in4[i]);
    // }
    // AES_ECB_decrypt(&ctx, in4);
    // printf("]\nECB decrypted: [");
    // for (size_t i = 0; i < insize; i++) {
    //     printf("%c", in4[i]);
    // }
    // printf("]\n\n");
    //
    // unsigned char out[] = "McpFEli%zT0IjvZLGTg$ihIw";
    // AES_ECB_decrypt(&ctx, out);
    // printf("]\nECB decrypted: [");
    // for (size_t i = 0; i < insize; i++) {
    //     printf("%c", in4[i]);
    // }
    // printf("]\n\n");

}
