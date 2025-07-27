#ifndef PROTO_H
#define PROTO_H

#include <stdio.h>
#include <stdint.h>

void handleInterrupt(int signal);
void disableInputBuffering(void);
void restoreInputBuffering(void);
uint16_t checkKey(void);
void readImageFile(FILE* file);
uint16_t swap16(uint16_t x);
int readImage(const char* image_path);
uint16_t signExtend(uint16_t x, int bit_count);
void updateFlags(uint16_t r);
void memWrite(uint16_t address, uint16_t val);
uint16_t memRead(uint16_t address);

#endif // PROTO_H
