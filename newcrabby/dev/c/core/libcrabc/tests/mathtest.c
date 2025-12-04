#include <stdio.h>
#include "../include/mmath.h"

int main(void) {
    int arra[] = { 4, 1, 9, 8, 2, 4, 3, 0 };
    int arrb[] = { 3, 5, 5, 9, 2, 6, 1, 0, 3, 4, 2, 8 };
    int arrc[] = { 3, 2, 1, 6, 5, 4, 9, 8, 7 };
    Matrix* mA = CreateMatrix(arra, 2, 4);
    Matrix* mB = CreateMatrix(arrb, 4, 3);
    Matrix* mC = CreateMatrix(arrc, 3, 3);

    Matrix* mAxB = MatrixMultiply(mA, mB);
    PrintMatrix(mAxB);

    Matrix* mBxC = MatrixMultiply(mB, mC);
    PrintMatrix(mBxC);

    FreeMatrix(mA);
    FreeMatrix(mB);
    FreeMatrix(mC);
    FreeMatrix(mAxB);
    FreeMatrix(mBxC);
    return 0;
}
