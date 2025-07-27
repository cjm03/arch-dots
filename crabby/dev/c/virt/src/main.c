/*
 * A virtual machine for running either rogue or 2048.
 *
 * Compile: gcc main.c -O3 -o virt
 *
 * Run: ./virt <path/to/obj>
 *      ./virt /home/crab/crabby/dev/c/virt/support/2048.obj
 *      ./virt /home/crab/crabby/dev/c/virt/support/rogue.obj
 *
 *
 *
 *
 * Source: https://github.com/justinmeiners/lc3-vm/
 *
 * Guide: https://www.jmeiners.com/lc3-vm/
*/


#include <iso646.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

typedef enum {
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC, /* program counter */
    R_COND,
    R_COUNT
} Registers;

typedef enum {
    OP_BR = 0,  /*         branch         */
    OP_ADD,     /*          add           */
    OP_LD,      /*          load          */
    OP_ST,      /*         store          */
    OP_JSR,     /*      jump register     */
    OP_AND,     /*      bitwise and       */
    OP_LDR,     /*      load register     */
    OP_STR,     /*      store register    */
    OP_RTI,     /*          unused        */
    OP_NOT,     /*       bitwise not      */
    OP_LDI,     /*      load indirect     */
    OP_STI,     /*      store indirect    */
    OP_JMP,     /*         jump           */
    OP_RES,     /*   reserved (unused)    */
    OP_LEA,     /* load effective address */
    OP_TRAP,    /*      execute trap      */
} Opcodes;

/* `<<` is the left bitshift operator. 1 << 2 will equal 4 (001 -> 100) */
typedef enum {
    FL_POS = 1 << 0,    /* P */
    FL_ZRO = 1 << 1,    /* Z */
    FL_NEG = 1 << 2,    /* N */
} ConditionFlags;

typedef enum {
    TRAP_GETC = 0x20,
    TRAP_OUT = 0x21,
    TRAP_PUTS = 0x22,
    TRAP_IN = 0x23,
    TRAP_PUTSP = 0x24,
    TRAP_HALT = 0x25
} TRAPCodes;

typedef enum {
    MR_KBSR = 0xFE00,
    MR_KBDR = 0xFE02
} MemMappedRegs;

#define MEMORY_MAX (1 << 16)
/* Memory Storage: 65536 locations */
uint16_t memory[MEMORY_MAX];

/* Register Storage */
uint16_t reg[R_COUNT];

struct termios original_tio;

///////////////////////////////////////////////
// functions
///////////////////////////////////////////////
void disableInputBuffering(void)
{
    tcgetattr(STDIN_FILENO, &original_tio);
    struct termios new_tio = original_tio;
    new_tio.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}
void restoreInputBuffering(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}
uint16_t checkKey(void)
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    return select(1, &readfds, NULL, NULL, &timeout) != 0;
}
void handleInterrupt(int signal)
{
    restoreInputBuffering();
    printf("\n");
    exit(-2);
}
uint16_t signExtend(uint16_t x, int bit_count)
{
    if ((x >> (bit_count - 1)) & 1) {
        x |= (0xFFFF << bit_count);
    }
    return x;
}
uint16_t swap16(uint16_t x)
{
    return (x << 8) | (x >> 8);
}
void updateFlags(uint16_t r)
{
    if (reg[r] == 0) reg[R_COND] = FL_ZRO;
    else if (reg[r] >> 15) reg[R_COND] = FL_NEG;
    else reg[R_COND] = FL_POS;
}
void readImageFile(FILE* file)
{
    /* origin tells us where in memory to place the image */
    uint16_t origin;
    fread(&origin, sizeof(origin), 1, file);
    origin = swap16(origin);

    /* we know max file size so we only need one fread */
    uint16_t max_read = MEMORY_MAX - origin;
    uint16_t* p = memory + origin;
    size_t read = fread(p, sizeof(uint16_t), max_read, file);

    /* swap to little endian */
    while (read-- > 0) {
        *p = swap16(*p);
        ++p;
    }
}
int readImage(const char* image_path)
{
    FILE* file = fopen(image_path, "rb");
    if (!file) return 0;
    readImageFile(file);
    fclose(file);
    return 1;
}
void memWrite(uint16_t address, uint16_t val)
{
    memory[address] = val;
}
uint16_t memRead(uint16_t address)
{
    if (address == MR_KBSR) {
        if (checkKey()) {
            memory[MR_KBSR] = (1 << 15);
            memory[MR_KBDR] = getchar();
        } else {
            memory[MR_KBSR] = 0;
        }
    }
    return memory[address];
}

int main(int argc, const char* argv[])
{
    if (argc < 2) {
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }
    
    for (int j = 1; j < argc; ++j) {
        if (!readImage(argv[j])) {
            printf("failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }

    signal(SIGINT, handleInterrupt);
    disableInputBuffering();

    reg[R_COND] = FL_ZRO;

    enum { PC_START = 0x3000 };
    reg[R_PC] = PC_START;

    int running = 1;
    while (running) {
        uint16_t instr = memRead(reg[R_PC]++);
        uint16_t op = instr >> 12;

        switch (op) {
            case OP_BR: {
                uint16_t pc_offset = signExtend(instr & 0x1FF, 9);
                uint16_t cond_flag = (instr >> 9) & 0x7;
                if (cond_flag & reg[R_COND]) {
                    reg[R_PC] += pc_offset;
                }
            }
            break;
            case OP_ADD: {
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t r1 = (instr >> 6) & 0x7;
                uint16_t imm_flag = (instr >> 5) & 0x1;
                if (imm_flag) {
                    uint16_t imm5 = signExtend(instr & 0x1F, 5);
                    reg[r0] = reg[r1] + imm5;
                } else {
                    uint16_t r2 = instr & 0x7;
                    reg[r0] = reg[r1] + reg[r2];
                }
                updateFlags(r0);
                
            }
            break;
            case OP_LD: {
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t pc_offset = signExtend(instr & 0x1FF, 9);
                reg[r0] = memRead(reg[R_PC] + pc_offset);
                updateFlags(r0);
                
            }
            break;
            case OP_ST: {
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t pc_offset = signExtend(instr & 0x1FF, 9);
                memWrite(reg[R_PC] + pc_offset, reg[r0]);
                
            }
            break;
            case OP_JSR: {
                uint16_t long_flag = (instr >> 11) & 1;
                reg[R_R7] = reg[R_PC];
                if (long_flag) {
                    uint16_t long_pc_offset = signExtend(instr & 0x7FF, 11);
                    reg[R_PC] += long_pc_offset;
                } else {
                    uint16_t r1 = (instr >> 6) & 0x7;
                    reg[R_PC] = reg[r1];
                }
                
            }
            break;
            case OP_AND: {
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t r1 = (instr >> 6) & 0x7;
                uint16_t imm_flag = (instr >> 5) & 0x1;

                if (imm_flag) {
                    uint16_t imm5 = signExtend(instr & 0x1F, 5);
                    reg[r0] = reg[r1] & imm5;
                } else {
                    uint16_t r2 = instr & 0x7;
                    reg[r0] = reg[r1] & reg[r2];
                }
                updateFlags(r0);
                
            }
            break;
            case OP_LDR: {
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t r1 = (instr >> 6) & 0x7;
                uint16_t offset = signExtend(instr & 0x3F, 6);
                reg[r0] = memRead(reg[r1] + offset);
                updateFlags(r0);
                
            }
            break;
            case OP_STR: {
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t r1 = (instr >> 6) & 0x7;
                uint16_t offset = signExtend(instr & 0x3F, 6);
                memWrite(reg[r1] + offset, reg[r0]);
                
            }
            break;
            case OP_NOT: {
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t r1 = (instr >> 6) & 0x7;
                reg[r0] = ~reg[r1];
                updateFlags(r0);
                
            }
            break;
            case OP_LDI: {
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t pc_offset = signExtend(instr & 0x1FF, 9);
                reg[r0] = memRead(memRead(reg[R_PC] + pc_offset));
                updateFlags(r0);
                
            }
            break;
            case OP_STI: {
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t pc_offset = signExtend(instr & 0x1FF, 9);
                memWrite(memRead(reg[R_PC] + pc_offset), reg[r0]);
                
            }
            break;
            case OP_JMP: {
                uint16_t r1 = (instr >> 6) & 0x7;
                reg[R_PC] = reg[r1];
                
            }
            break;
            case OP_LEA: {
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t pc_offset = signExtend(instr & 0x1FF, 9);
                reg[r0] = reg[R_PC] + pc_offset;
                updateFlags(r0);
                
            }
            break;
            case OP_TRAP: {
                reg[R_R7] = reg[R_PC];
                switch (instr & 0xFF) {
                    case TRAP_GETC: {
                        reg[R_R0] = (uint16_t)getchar();
                        updateFlags(R_R0);
                        break;
                    }
                    case TRAP_OUT: {
                        putc((char)reg[R_R0], stdout);
                        fflush(stdout);
                        break;
                    }
                    case TRAP_PUTS: {
                        uint16_t* c = memory + reg[R_R0];
                        while (*c) {
                            putc((char)*c, stdout);
                            ++c;
                        }
                        fflush(stdout);
                        break;
                    }
                    case TRAP_IN: {
                        printf("Enter a character: ");
                        char c = getchar();
                        putc(c, stdout);
                        fflush(stdout);
                        reg[R_R0] = (uint16_t)c;
                        updateFlags(R_R0);
                        break;
                    }
                    case TRAP_PUTSP: {
                        uint16_t* c = memory + reg[R_R0];
                        while (*c)
                        {
                            char char1 = (*c) & 0xFF;
                            putc(char1, stdout);
                            char char2 = (*c) >> 8;
                            if (char2) putc(char2, stdout);
                            ++c;
                        }
                        fflush(stdout);
                        break;
                    }
                    case TRAP_HALT: {
                        puts("HALT");
                        fflush(stdout);
                        running = 0;
                        break;
                    }
                }
            }
            break;
            case OP_RES:
            case OP_RTI:
            default:
                abort();
                break;
        }
    }
    restoreInputBuffering();
}







