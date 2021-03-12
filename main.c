#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

int main(int argc, char **argv)
{
    // int row = 2;
    // int column = 2;
    // float **matrix = (float**)malloc(row*sizeof(float*));
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = 3;
    matrix->columns = 2;
    matrix->cells = (float**)malloc(matrix->rows*sizeof(float*));

    for (int i = 0; i < matrix->rows; i++) {
        // *(matrix+i) = (float*)malloc(column*sizeof(float));
        *(matrix->cells+i) = (float*)malloc(matrix->columns*sizeof(float));
        for (int j = 0; j < matrix->columns; j++) {
            // if (((i+1)+(j+1))%2 == 0) *(*(matrix+i)+j) = 2*i+j;
            // else *(*(matrix+i)+j) = (1+i)*(1+j);
            if (((i+1)+(j+1))%2 == 0) *(*(matrix->cells+i)+j) = 2*i+j;
            else *(*(matrix->cells+i)+j) = (1+i)*(1+j);
        }
    }

    // // Show matrix
    printf("-----------------Matrix-----------------\n");
    displayMatrix(matrix);
    printf("-----------------END-----------------\n");

    Matrix *transp = transpose(matrix);
    printf("-----------------Transpose-----------------\n");
    displayMatrix(transp);
    printf("-----------------END-----------------\n");

    // float **mult = multiply(matrix, row, column, transp, column, row);
    // printf("-----------------Multiply-----------------\n");
    // displayMatrix(mult, row, row);
    // printf("-----------------END-----------------\n");

    // float det = determinant(matrix, 3, 3, 3); // Matrix a se descobrir o determinante, linhas, colunas, mair indice da matriz
    // printf("-----------------Determinant-----------------\n");
    // printf("%.2f\n", det);
    // printf("-----------------END-----------------\n");

    // float **CxM = multiplyBy(mult, 3, 3, 0);
    // printf("-----------------MultiplyByConstant-----------------\n");
    // displayMatrix(CxM, 3, 3);
    // printf("-----------------END-----------------\n");

    // float **inv = inverse(mult, 3, 3);
    // printf("-----------------Inverse-----------------\n");
    // displayMatrix(inv, 3, 3);
    // printf("-----------------END-----------------\n");

    free(matrix);
    // free(transp);
    // free(mult);
    // free(CxM);

    matrix = NULL;
    // transp = NULL;
    // mult = NULL;
    // CxM = NULL;

    return 0;
}