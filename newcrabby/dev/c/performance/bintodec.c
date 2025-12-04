#include <stdio.h>


int main(void)
{
    // int num, bin, temp;
    // int dec = 0;
    // int topower = 0;
    unsigned long num, bin, temp;
    unsigned long dec = 0;
    unsigned long topower = 0;
    printf("Binary: ");
    scanf("%lu", &bin);
    temp = bin;
    while (bin > 0) {
        num = bin % 10;         // 1101011 % 10 = 1 or 0000001
        // printf("[%d mod 10 = %d]  ->  [%d", bin, num, num);
        num = num << topower;   // 0000001 << 0 = 0000001
        // printf(" << %d = %d]  ->  ", topower, num);
        dec = dec + num;        // 0000001 + 0 = 0000001
        topower++;
        // printf("[dec: %d, power: %d]  ->  ", dec, topower);
        bin = bin / 10;         // 1101011 / 10 = 110101.1
        // printf("%d\n", bin);
    }
    printf("decimal of %lu is %lu\n", temp, dec);
    return 0;
}
