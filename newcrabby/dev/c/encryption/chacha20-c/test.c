#include "chacha.c"
#include <stdint.h>

int main(void)
{
    Context Context;

    // 256-bit KEY
    uint8_t key[32] = {
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
        0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };

    // 96-bit NONCE
    uint8_t nonce[12] = {
        0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00
    };
    
    // 32-bit COUNTER
    uint32_t counter = 0;

    // variable length message to encrypt, converted to uint8_t array w/ StrToHex()
    const char* msg = "Despite the intense settings that we produce throughout the duration of the cat in the 9th life, there are few and far between minutes regarding; Four score and 7even years ago; $&!()(a despite/without) Ladies and gentlemen!";
    // const char* msg = "8NxkIc-wpNn82-Dtnszr-lNIROp";
    uint8_t data[strlen(msg)];
    StrToHex(msg, data, strlen(msg));

    // Print the message prior to encryption
    PRINTSERIALIZED(data, sizeof(data));

    // Initialize the ChaCha20 context
    CHACHA20_CONTEXT_INIT(&Context, key, nonce, counter, sizeof(data));

    // Perform the ChaCha20 algorithm
    CHACHA20_XOR(&Context, data, sizeof(data));

    // Print the encrypted message
    PRINTSERIALIZED(Context.buffer, sizeof(data));
    printf("raw: %s\n", Context.buffer);

    // Decrypt the encrypted message
    CHACHA20_DECRYPT(&Context, Context.buffer, sizeof(data));

    // Print the decrypted message
    PRINTSERIALIZED(Context.buffer, sizeof(data));

    // free allocations made to the heap
    free(Context.keystream);
    free(Context.buffer);
}
