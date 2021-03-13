#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

int main(int argc, char **argv)
{
    // int row = 2;
    // int column = 2;
    // float **matrix = (float**)malloc(row*sizeof(float*));
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = 2;
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

    Matrix *mult = multiply(matrix, transp);
    printf("-----------------Multiply-----------------\n");
    displayMatrix(mult);
    printf("-----------------END-----------------\n");

    float det = determinant(mult, matrix->rows); // Matrix a se descobrir o determinante, linhas, colunas, mair indice da matriz
    printf("-----------------Determinant-----------------\n");
    printf("%.2f\n", det);
    printf("-----------------END-----------------\n");

    Matrix *CxM = multiplyBy(mult, 2);
    printf("-----------------MultiplyByConstant-----------------\n");
    displayMatrix(CxM);
    printf("-----------------END-----------------\n");

    Matrix *inv = inverse(mult);
    printf("-----------------Inverse-----------------\n");
    displayMatrix(inv);
    printf("-----------------END-----------------\n");

    free(matrix);
    free(transp);
    free(mult);
    free(CxM);
    free(inv);

    matrix = NULL;
    transp = NULL;
    mult = NULL;
    CxM = NULL;
    inv = NULL;

    return 0;
}