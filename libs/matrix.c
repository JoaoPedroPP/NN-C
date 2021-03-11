#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

void displayMatrix(float **A, int rows, int columns)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%.2f ", *(*(A+i)+j));
        }
        printf("\n");
    }
}

void recursiveTranspose(float **T, float **m, int column, int row)
{
    if (row == 0 || column == 0) return;
    else {
        if (*(T+row-1) == NULL) *(T+row-1) = (float*)malloc(column*sizeof(float));
        *(*(T+row-1)+column-1) = *(*(m+column-1)+row-1);
        recursiveTranspose(T, m, column-1, row);
        recursiveTranspose(T, m, column, row-1);
        return;
    }
}

float** transpose(float **m, int row, int column)
{
    float **transpose = (float**)malloc(column*sizeof(float*));
    recursiveTranspose(transpose, m, row, column);
    // displayMatrix(transpose, column, row);
    // for (int i = 0; i < column; i++) {
    //     *(transpose+i) = (float*)malloc(row*sizeof(float));
    //     for (int j = 0; j < row; j++) {
    //         *(*(transpose+i)+j) = *(*(m+j)+i);
    //     }
    // }

    return transpose;
}

float recursiveMultiplyElement(float **m1, float **m2, int row, int column, int n)
{
    if (n == 1) return *(*(m1+row-1)+n-1) * *(*(m2+n-1)+column-1);
    return recursiveMultiplyElement(m1, m2, row, column, n-1) + *(*(m1+row-1)+n-1) * *(*(m2+n-1)+column-1);
}

void recursiveMultiply(float **M, float **m1, float **m2, int row, int column, int n)
{
    if (row == 0 || column == 0) return;
    else {
        if (*(M+row-1) == NULL) *(M+row-1) = (float*)malloc(column*sizeof(float));
        *(*(M+row-1)+column-1) = recursiveMultiplyElement(m1, m2, row, column, n); // WORKS!!!
        // *(*(M+row-1)+column-1) = *(*(M+row-1)+column-1) + *(*(m1+row-1)+n-1) * *(*(m2+n-1)+column-1);
        // recursiveMultiply(M, m1, m2, row, column, n-1);
        recursiveMultiply(M, m1, m2, row, column-1, n);
        recursiveMultiply(M, m1, m2, row-1, column, n);
        return;

    }
}

float** multiply(float **m1, int row_1, int column_1, float **m2, int row_2, int column_2)
{
    if (column_1 == row_2) {
        float **result = (float**)malloc(row_1*sizeof(float*));
        recursiveMultiply(result, m1, m2, row_1, column_2, row_2);
        // displayMatrix(result, row_1, column_2);
        // for (int i = 0; i < row_1; i++) {
        //     *(result+i) = (float*)malloc(column_2*sizeof(float));
        //     for (int j = 0; j < column_2; j++) {
        //         *(*(result + i) + j) = 0;
        //         for (int m = 0; m < column_1; m++) {
        //             *(*(result + i) + j) = *(*(result + i) + j) + *(*(m1+i)+m) * *(*(m2+m)+j);
        //         }
        //     }
        // }
        return result;
    }
    else {
        return NULL;
    }
}

void recursiveMultiplyBy(float **result, float **A, int rows, int columns, float constant)
{
    if (rows == 0 || columns == 0) return;
    else {
        if (*(result+rows-1) == NULL) *(result+rows-1) = (float*)malloc(columns*sizeof(float));
        *(*(result+rows-1)+columns-1) = constant * *(*(A+rows-1)+columns-1);
        recursiveMultiplyBy(result, A, rows, columns-1, constant);
        recursiveMultiplyBy(result, A, rows-1, columns, constant);
        return;
    }
}

float** multiplyBy(float **A, int rows, int columns, float constant)
{
    float **B = (float**)malloc(rows*sizeof(float*));
    recursiveMultiplyBy(B, A, rows, columns, constant);
    // displayMatrix(B, rows, columns);
    // for (int i = 0; i < rows; i++) {
    //     *(B+i) = (float*)malloc(columns*sizeof(float));
    //     for (int j = 0; j < columns; j++) {
    //         *(*(B+i)+j) = constant * *(*(A+i)+j);
    //     }
    // }
    return B;
}

float** cofactor(float **A, int rows, int columns, int i, int j)
{
    float **C = (float**)malloc((rows-1)*sizeof(float*));
    int n = 0;
    int m = 0;
    while (n < i) {
        *(C+n) = (float*)malloc((columns-1)*sizeof(float));
        m = 0;
        while (m < j) {
            *(*(C+n)+m) = *(*(A+n)+m);
            m++;
        }
        m++;
        while (m < columns) {
            *(*(C+n)+m-1) = *(*(A+n)+m);
            m++;
        }
        n++;
    }
    n++;
    while (n < rows) {
        *(C+n-1) = (float*)malloc((columns-1)*sizeof(float));
        m = 0;
        while (m < j) {
            *(*(C+n-1)+m) = *(*(A+n)+m);
            m++;
        }
        m++;
        while (m < columns) {
            *(*(C+n-1)+m-1) = *(*(A+n)+m);
            m++;
        }
        n++;
    }
    return C;
}

float determinant(float **A, int rows, int columns, int position)
{
    if (rows == columns && rows == 2) return **A * *(*(A+rows-1)+columns-1) - *(*(A)+columns-1) * **(A+rows-1);
    else if (position < 1 || rows < 0) return 0;
    else {
        if ((rows+position)%2 == 0) return *(*(A+rows-1)+position-1) * determinant(cofactor(A, rows, columns, rows-1, position-1), rows-1, columns-1, columns-1) + determinant(A, rows, columns, position-1);
        else return (-1) * *(*(A+rows-1)+position-1) * determinant(cofactor(A, rows, columns, rows-1, position-1), rows-1, columns-1, columns-1) + determinant(A, rows, columns, position-1);
    }
}