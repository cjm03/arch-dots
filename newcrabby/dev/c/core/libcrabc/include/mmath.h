// mmath.h
// ███╗   ███╗███╗   ███╗ █████╗ ████████╗██╗  ██╗
// ████╗ ████║████╗ ████║██╔══██╗╚══██╔══╝██║  ██║
// ██╔████╔██║██╔████╔██║███████║   ██║   ███████║
// ██║╚██╔╝██║██║╚██╔╝██║██╔══██║   ██║   ██╔══██║
// ██║ ╚═╝ ██║██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║
// ╚═╝     ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝
//
// Headerfile for mmath.c. Hardly useful atm
//
// Charlie Moye
// 11-12-2025


#ifndef MMATH_H
#define MMATH_H

typedef struct Matrix {
    int rows;
    int cols;
    int** data;
} Matrix;

#define GetMatrixRows(matrix) (sizeof(matrix) / sizeof(matrix[0]))
#define GetMatrixCols(matrix) (sizeof(matrix[0]) / sizeof(matrix[0][0]))

/**
 *
 */
Matrix* CreateMatrix(int* data, int rows, int cols);

/**
 *
 */
Matrix* MatrixAdd(Matrix* a, Matrix* b);

/**
 *
 */
Matrix* MatrixSub(Matrix* a, Matrix* b);

/**
 *
 */
void MatrixScale(Matrix* m, int scale);

/**
 *
 */
Matrix* MatrixTranspose(Matrix* m);

/**
 *
 */
Matrix* MatrixMultiply(Matrix* a, Matrix* b);

/**
 *
 */
void PrintMatrix(Matrix* m);

/**
 *
 */
void FreeMatrix(Matrix* m);

#endif // MMATH_H
