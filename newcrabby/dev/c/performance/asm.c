/*
 * +------------+---------------------------------------------------------------+
 * | Constraint | Usage                                                         |
 * +------------+---------------------------------------------------------------+
 * | g          + Compiler will decide the register to be used for the variable |
 * +------------+---------------------------------------------------------------+
 * | r          + Load into any available register                              |
 * +------------+---------------------------------------------------------------+
 * | a          + Load into the eax register                                    |
 * +------------+---------------------------------------------------------------+
 * | b          + Load into the ebx register                                    |
 * +------------+---------------------------------------------------------------+
 * | c          + Load into the ecx register                                    |
 * +------------+---------------------------------------------------------------+
 * | d          + Load into the edx register                                    |
 * +------------+---------------------------------------------------------------+
 * | f          + Load into the floating-point register                         |
 * +------------+---------------------------------------------------------------+
 * | D          + Load into the edi register                                    |
 * +------------+---------------------------------------------------------------+
 * | S          + Load into the esi register                                    |
 * +------------+---------------------------------------------------------------+
 *
 * Load the two values into eax and ebx registers
 * Multiply the contents of the eax and ebx registers and store in the eax register
 * Display the contents of the eax register on the screen
*/

#include <stdio.h>
#include <stdint.h>

void mult(int32_t x, int32_t y)
{
    int32_t multi = 0;
    asm volatile ("imull %%ebx,%%eax;"
        : "=a" (multi)
        : "a" (x), "b" (y)
    );
    printf("Multiplication: %d * %d = %d\n", x, y, multi);
}

void divide(int32_t x, int32_t y)
{
    int32_t var3 = 0, rem, quot;
    asm("divl %%ebx;"                       // divide eax by ebx
        "movl %%edx, %0"                    // load 0 into edx
        : "=b" (rem), "=r" (quot)           // load value in ebx into rem, load value in other availabe register into quot
        : "a" (x), "b" (y), "d" (var3)      // load x into eax, load y into ebx, load var3 into edx
    );
    printf("Divide: %d / %d = %d R %d\n", x, y, quot, rem);
}

int main(int argc, char** argv)
{
    int32_t h=10, i=20, j=19, k=4;
    mult(h, i);
    divide(j, k);
    return 0;
}
