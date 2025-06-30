#include <stdio.h>
#include "prime.h"

int main(void)
{
    int x = 256;
    int isp = isPrime(x);
    printf("isPrime(x): %d\n", isp);
    int y = nextPrime(x);
    printf("%d next prime is %d\n", x, y);
}
