#include <stdio.h>
#include <stdlib.h>

#include "../include/mmath.h"
#include "../include/define.h"

Matrix* CreateMatrix(int* data, int rows, int cols) {
    Matrix* m = malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        int* temp = malloc(sizeof(int) * cols);
        for (int j = 0; j < cols; j++) {
            temp[j] = data[i * cols + j];
        }
        m->data[i] = temp;
    }
    return m;
}

Matrix* MatrixAdd(Matrix* a, Matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols) {
        fprintf(stderr, "error: cannot add matrices of differing sizes\n");
        return NULL;
    }
    int* temp = malloc(sizeof(int) * (a->rows * a->cols));
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            temp[i * a->cols + j] = a->data[i][j] + b->data[i][j];
        }
    }
    Matrix* m = CreateMatrix(temp, a->rows, a->cols);
    free(temp);
    return m;
}

Matrix* MatrixSub(Matrix* a, Matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols) {
        fprintf(stderr, "error: cannot add matrices of differing sizes\n");
        return NULL;
    }
    int* temp = malloc(sizeof(int) * (a->rows * a->cols));
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            temp[i * a->cols + j] = a->data[i][j] - b->data[i][j];
        }
    }
    Matrix* m = CreateMatrix(temp, a->rows, a->cols);
    free(temp);
    return m;
}

void MatrixScale(Matrix* m, int scale) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->data[i][j] *= scale;
        }
    }
}

Matrix* MatrixTranspose(Matrix* m) {
    int* temp = malloc(sizeof(int) * (m->rows * m->cols));
    for (int i = 0; i < m->cols; i++) {
        for (int j = 0; j < m->rows; j++) {
            temp[i * m->rows + j] = m->data[j][i];
        }
    }
    Matrix* new = CreateMatrix(temp, m->cols, m->rows);
    free(temp);
    return new;
}

Matrix* MatrixMultiply(Matrix* a, Matrix* b) {
    if (a->cols != b->rows) {
        fprintf(stderr, "Cannot multiply %dx%d matrix with %dx%d matrix\n", a->rows, a->cols, b->rows, b->cols);
        return NULL;
    }
    int* temp = malloc(sizeof(int) * (a->rows * b->cols));
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            int result = 0;
            for (int k = 0; k < b->rows; k++) {
                result += a->data[i][k] * b->data[k][j];
            }
            temp[i * b->cols + j] = result;
        }
    }
    Matrix* new = CreateMatrix(temp, a->rows, b->cols);
    free(temp);
    return new;
}

void PrintMatrix(Matrix* m) {
    printf("Matrix: %dx%d\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        printf("[ ");
        for (int j = 0; j < m->cols; j++) {
            printf("%02d ", m->data[i][j]);
        }
        printf("]\n");
    }
}

void FreeMatrix(Matrix* m) {
    for (int i = 0; i < m->rows; i++) free(m->data[i]);
    free(m->data);
    free(m);
}
