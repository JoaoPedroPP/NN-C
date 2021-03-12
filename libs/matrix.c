#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

void displayMatrix(Matrix *A)
{
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            printf("%.2f ", *(*(A->cells+i)+j));
        }
        printf("\n");
    }
}

void recursiveTranspose(Matrix *T, Matrix *m, int column, int row)
{
    if (row == 0 || column == 0) return;
    else {
        if (*(T->cells+row-1) == NULL) *(T->cells+row-1) = (float*)malloc(T->columns*sizeof(float));
        *(*(T->cells+row-1)+column-1) = *(*(m->cells+column-1)+row-1);
        recursiveTranspose(T, m, column-1, row);
        recursiveTranspose(T, m, column, row-1);
        return;
    }
}

Matrix* transpose(Matrix *A)
{
    Matrix *T = (Matrix*)malloc(sizeof(Matrix*));
    T->rows = A->columns;
    T->columns = A->rows;
    T->cells = (float**)malloc(T->rows*sizeof(float*));
    recursiveTranspose(T, A, A->rows, A->columns);

    return T;
}

float recursiveMultiplyElement(Matrix *m1, Matrix *m2, int row, int column, int n)
{
    if (n == 1) return *(*(m1->cells+row-1)+n-1) * *(*(m2->cells+n-1)+column-1);
    return recursiveMultiplyElement(m1, m2, row, column, n-1) + *(*(m1->cells+row-1)+n-1) * *(*(m2->cells+n-1)+column-1);
}

void recursiveMultiply(Matrix *M, Matrix *m1, Matrix *m2, int row, int column, int n)
{
    if (row == 0 || column == 0) return;
    else {
        if (*(M->cells+row-1) == NULL) *(M->cells+row-1) = (float*)malloc(column*sizeof(float));
        *(*(M->cells+row-1)+column-1) = recursiveMultiplyElement(m1, m2, row, column, n); // WORKS!!!
        recursiveMultiply(M, m1, m2, row, column-1, n);
        recursiveMultiply(M, m1, m2, row-1, column, n);
        return;

    }
}

Matrix* multiply(Matrix *A, Matrix *B)
{
    if (A->columns == B->rows) {
        Matrix *result = (Matrix*)malloc(sizeof(Matrix));
        result->rows = A->rows;
        result->columns = B->columns;
        result->cells = (float**)malloc(result->rows*sizeof(float*));
        recursiveMultiply(result, A, B, A->rows, B->columns, B->rows);
        return result;
    }
    else {
        return NULL;
    }
}

void recursiveMultiplyBy(Matrix *result, Matrix *A, int rows, int columns, float constant)
{
    if (rows == 0 || columns == 0) return;
    else {
        if (*(result->cells+rows-1) == NULL) *(result->cells+rows-1) = (float*)malloc(result->columns*sizeof(float));
        *(*(result->cells+rows-1)+columns-1) = constant * *(*(A->cells+rows-1)+columns-1);
        recursiveMultiplyBy(result, A, rows, columns-1, constant);
        recursiveMultiplyBy(result, A, rows-1, columns, constant);
        return;
    }
}

Matrix* multiplyBy(Matrix *A, float constant)
{
    Matrix *B = (Matrix*)malloc(sizeof(Matrix));
    B->rows = A->rows;
    B->columns = A->columns;
    B->cells = (float**)malloc(B->rows*sizeof(float*));
    recursiveMultiplyBy(B, A, A->rows, B->columns, constant);
    return B;
}

Matrix* cofactor(Matrix *A, int i, int j)
{
    Matrix *C = (Matrix*)malloc(sizeof(Matrix));
    C->rows = A->rows-1;
    C->columns = A->columns-1;
    C->cells = (float**)malloc(C->rows*sizeof(float*));
    int n = 0;
    int m = 0;
    while (n < i) {
        *(C->cells+n) = (float*)malloc(C->columns*sizeof(float));
        m = 0;
        while (m < j) {
            *(*(C->cells+n)+m) = *(*(A->cells+n)+m);
            m++;
        }
        m++;
        while (m < A->columns) {
            *(*(C->cells+n)+m-1) = *(*(A->cells+n)+m);
            m++;
        }
        n++;
    }
    n++;
    while (n < A->rows) {
        *(C->cells+n-1) = (float*)malloc(C->columns*sizeof(float));
        m = 0;
        while (m < j) {
            *(*(C->cells+n-1)+m) = *(*(A->cells+n)+m);
            m++;
        }
        m++;
        while (m < A->columns) {
            *(*(C->cells+n-1)+m-1) = *(*(A->cells+n)+m);
            m++;
        }
        n++;
    }
    // displayMatrix(C);
    return C;
}

float determinant(Matrix *A, int position)
{
    // displayMatrix(A);
    if (A->rows != A->columns) return 0;
    else {
        if (A->rows == 2) return **(A->cells) * *(*(A->cells+A->rows-1)+A->columns-1) - *(*(A->cells)+A->columns-1) * **(A->cells+A->rows-1);
        else if (position < 1 || A->rows < 0) return 0;
        else {
            if ((A->rows+position)%2 == 0) return *(*(A->cells+A->rows-1)+position-1) * determinant(cofactor(A, A->rows-1, position-1), A->columns-1) + determinant(A, position-1);
            else return (-1) * *(*(A->cells+A->rows-1)+position-1) * determinant(cofactor(A, A->rows-1, position-1), A->columns-1) + determinant(A, position-1);
        }
    }
}

void inverseRecursive(Matrix *A, int row, int column)
{
    // if (row == 0 || column == 0 || 0) return;
    // else if (column == 0) return;
    // else {
        // if (*(A->cells+row-1) == NULL) *(A->cells+row-1) = (float*)malloc(A->columns*sizeof(float));
        // if ((row+column)%2 == 0) *(*(A->cells+row-1)+column-1) = determinant(cofactor(A, row-1, column-1), A->rows-1);
        // else *(*(A->cells+row-1)+column-1) = -1 * determinant(cofactor(A, row-1, column-1), A->rows-1);
        printf("%dx%d\n", row-1, column-1);
        // *(*(A->cells+row-1)+column-1) = determinant(cofactor(A, row-1, column-1), A->rows-1);
        // *(*(A->cells+row-1)+column-1) = 1;
        // printf("%.2f\n", *(*(A->cells+row-1)+column-1));
        // Matrix *a = cofactor(A, 0, 0);
        // Matrix *a = cofactor(A, 2, 2);
        Matrix *B = (Matrix*)malloc(sizeof(Matrix));
        B->rows = 4;
        B->columns = 4;
        for (int i = 0; i < B->rows; i++) {
        printf("%dx%d\n", B->rows, B->columns);
            *(B->cells+i) = (float*)malloc(B->columns*sizeof(float));
            for (int j = 0; j < B->columns; j++) {
                *(*(B->cells+i)+j) = i+j+2;
            }
        }
        displayMatrix(B);
        // printf("%dx%d\n", A->rows, A->columns);
        // float x = determinant(A, A->rows);
        // printf("%.2f\n", x);
        // inverseRecursive(A, row, column-1);
        // inverseRecursive(A, row-1, column);
        return;
    // }
}

Matrix* inverse(Matrix *A) // not work for 2x2
{
    Matrix *result = (Matrix*)malloc(sizeof(Matrix));
    result->rows = A->rows;
    result->columns = A->columns;
    result->cells = (float**)malloc(result->rows*sizeof(float*));
    float det = determinant(A, A->rows);
    printf("det: %.2f\n", det);
    inverseRecursive(result, result->rows, result->columns);
    for (int i = 0; i < result->rows; i++) {
        *(result->cells+i) = (float*)malloc(result->columns*sizeof(float));
        for (int j = 0; j < result->columns; j++) {
            if ((i+j+2)%2 == 0) *(*(result->cells+i)+j) = determinant(cofactor(A, i, j), result->rows-1);
            else *(*(result->cells+i)+j) = -1 * determinant(cofactor(A, i, j), result->rows-1);
        }
    }
    result = multiplyBy(result, 1/det);
    return result;
}