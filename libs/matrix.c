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
    if (row == 0) return;
    else if (column == 0) recursiveTranspose(T, m, T->columns, row-1);
    else {
        if (*(T->cells+row-1) == NULL) *(T->cells+row-1) = (float*)malloc(T->columns*sizeof(float));
        *(*(T->cells+row-1)+column-1) = *(*(m->cells+column-1)+row-1);
        recursiveTranspose(T, m, column-1, row);
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
    if (row == 0) return;
    else if (column == 0) recursiveMultiply(M, m1, m2, row-1, M->columns, n);
    else {
        if (*(M->cells+row-1) == NULL) *(M->cells+row-1) = (float*)malloc(column*sizeof(float));
        *(*(M->cells+row-1)+column-1) = recursiveMultiplyElement(m1, m2, row, column, n); // WORKS!!!
        recursiveMultiply(M, m1, m2, row, column-1, n);
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
    if (rows == 0) return;
    else if (columns == 0) recursiveMultiplyBy(result, A, rows-1, result->columns, constant);
    else {
        if (*(result->cells+rows-1) == NULL) *(result->cells+rows-1) = (float*)malloc(result->columns*sizeof(float));
        *(*(result->cells+rows-1)+columns-1) = constant * *(*(A->cells+rows-1)+columns-1);
        recursiveMultiplyBy(result, A, rows, columns-1, constant);
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

Matrix* cofactor2x2(Matrix *A)
{
    Matrix *C = (Matrix*)malloc(sizeof(Matrix));
    C->rows = A->rows;
    C->columns = A->columns;
    C->cells = (float**)malloc(C->rows*sizeof(float*));
    *(C->cells) = (float*)malloc(C->columns*sizeof(float));
    *(C->cells+1) = (float*)malloc(C->columns*sizeof(float));

    **C->cells = *(*(A->cells+1)+1); // 1x1 = 2x2
    **(C->cells+1) = -1 * *(*(A->cells)+1); // 2x1 = 1x2
    *(*(C->cells)+1) = -1 * **(A->cells+1); // 1x2 = 2x1
    *(*(C->cells+1)+1) = **(A->cells); // 2x2 = 1x1

    return C;
}

float determinant(Matrix *A, int position)
{
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

void inverseRecursive(Matrix *A, Matrix *B, int row, int column)
{
    if (row == 0) return;
    else if (column == 0) inverseRecursive(A, B, row-1, A->columns);
    else {
        if (*(A->cells+row-1) == NULL) *(A->cells+row-1) = (float*)malloc(A->columns*sizeof(float));
        if ((row+column)%2 == 0) *(*(A->cells+row-1)+column-1) = determinant(cofactor(B, row-1, column-1), A->rows-1);
        else *(*(A->cells+row-1)+column-1) = -1 * determinant(cofactor(B, row-1, column-1), A->rows-1);
        inverseRecursive(A, B, row, column-1);
        return;
    }
}

Matrix* inverse(Matrix *A)
{
    if (A->rows == A->columns) {
        Matrix *result;
        if (A->rows == 2) {
            result = cofactor2x2(A);
        }
        else {
            result = (Matrix*)malloc(sizeof(Matrix));
            result->rows = A->rows;
            result->columns = A->columns;
            result->cells = (float**)malloc(result->rows*sizeof(float*));
            inverseRecursive(result, A, result->rows, result->columns);
        }
        float det = determinant(A, A->rows);
        return multiplyBy(result, 1/det);
    }
    else return NULL;
}

Matrix* SolveSystem(Matrix *A, Matrix *B)
{
    return multiply(inverse(A), B);
}

void sumRecurvise(Matrix *C, Matrix *A, Matrix *B, int row, int column)
{
    if (row == 0) return;
    else if (column == 0) sumRecurvise(C, A, B, row-1, C->columns);
    else {
        if (*(C->cells+row-1) == NULL) *(C->cells+row-1) = (float*)malloc(C->columns*sizeof(float));
        *(*(C->cells+row-1)+column-1) = *(*(A->cells+row-1)+column-1) + *(*(B->cells+row-1)+column-1);
        sumRecurvise(C, A, B, row, column-1);
    }
}

Matrix* sum(Matrix *A, Matrix *B)
{
    if (A->rows == B->rows && A->columns == B->columns) {
        Matrix *result = (Matrix*)malloc(sizeof(Matrix));
        result->rows = A->rows;
        result->columns = A->columns;
        result->cells = (float**)malloc(result->rows*sizeof(float*));
        sumRecurvise(result, A, B, result->rows, result->columns);
        return result;
    }
    else return NULL;
}