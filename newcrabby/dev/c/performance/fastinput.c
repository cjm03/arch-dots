#include <stdio.h>

int getData(void)
{
    char cdigit = getchar_unlocked();
    int cnum = 0;
    while (cdigit < '0' || cdigit > '9') cdigit = getchar_unlocked();
    while (cdigit >= '0' && cdigit <= '9') {
        cnum = 10 * cnum + cdigit - 48;
        cdigit = getchar_unlocked();
    }
    return cnum;
}

int main(void)
{
    int num;
    printf("Enter number: ");
    num = getData();
    printf("Entered number: %d\n", num);
    return 0;
}
