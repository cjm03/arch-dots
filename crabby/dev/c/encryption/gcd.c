#include <stdio.h>

long long gcd(long long a, long long b)
{
    long long first = a;
    long long second = b;
    long long r = first % second;
    long long q = (first - r) / second;
    printf("%lld = %lld * %lld + %lld\n", first, q, second, r);
    while (r > 0) {

        first = second;
        second = r;
        r = first % second;
        q = (first - r) / second;
        printf("%lld = %lld * %lld + %lld\n", first, q, second, r);

    }
    printf("gcd(%lld, %lld) = %lld\n", a, b, second);
    return second;
}
void charToBin(char ch)
{
    printf("%c: ", ch);
    for (int i = 7; i >= 0; i--) {
        if ((ch >> i) & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

int main(void)
{
    long long aone = 1160718174;
    long long btwo = 316258250;
    long long result = gcd(aone, btwo);
    char cone = 'c';
    charToBin(cone);
    char ctwo = 'r';
    charToBin(ctwo);
    char cthree = 'a';
    charToBin(cthree);
    char cfour = 'b';
    charToBin(cfour);
    char cfive = 'b';
    charToBin(cfive);
    char csix = 'y';
    charToBin(csix);
    printf("\n");
    return 0;
}
