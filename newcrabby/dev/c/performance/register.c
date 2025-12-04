/*
 *
*/

#include <stdio.h>
#include <string.h>

int main(void)
{
    int distance;
    char cartype[20];
    register int Acperkm, Nonacperkm, Servicetax;
    float carRent, totalrent;

    printf("Distance? (km): ");
    scanf("%d", &distance);
    printf("AC or non-AC? (ac or no): ");
    scanf("%s", cartype);
    Acperkm = 3;
    Nonacperkm = 2;
    Servicetax=1;

    if (strcmp(cartype, "ac") == 0) {
        carRent = distance * Acperkm;
    } else {
        carRent = distance * Nonacperkm;
    }
    totalrent = carRent + (carRent * Servicetax / 100);
    printf("Total rent: $%.2f\n", totalrent);
    return 0;
}
