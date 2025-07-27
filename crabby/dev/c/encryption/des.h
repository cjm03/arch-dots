#ifndef DES_H
#define DES_H

#define ACTION_GENKEY "-g"
#define ACTION_ENCRYPT "-e"
#define ACTION_DECRYPT "-d"
#define DESKEYSIZE 8
#define PLAINTEXTSIZE 64
#define ROUNDS 16

#define ENCRYPTION_MODE 1
#define DECRYPTION_MODE 0

typedef struct {
    unsigned char k[8];
    unsigned char c[4];
    unsigned char d[4];
} key_set;

void generateKey(unsigned char* key);
void generateSubKeys(unsigned char* main_key, key_set* key_sets);
void processMessage(unsigned char* msg, unsigned char* processed_msg, key_set* key_sets, int mode);

#endif // DES_H
