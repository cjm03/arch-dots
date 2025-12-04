#pragma once
#include <stdint.h>

// AES constants
#define  AES_KEY_SIZE     16
#define  AES_BLOCK_SIZE   16
#define  AES_PARAM_SIZE   2 * AES_BLOCK_SIZE
#define  AES_ROUNDS       10

#define ROTL8(x,shift) ((uint8_t) ((x) << (shift)) | ((x) >> (8 - (shift))))


void AES_init();
void AES_encrypt(uint8_t*, const uint8_t*);
