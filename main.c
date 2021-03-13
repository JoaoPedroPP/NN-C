#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

int main(int argc, char **argv)
{
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = 3;
    matrix->columns = 3;
    matrix->cells = (float**)malloc(matrix->rows*sizeof(float*));

    Matrix *b = (Matrix*)malloc(sizeof(Matrix));
    b->rows = 3;
    b->columns = 1;
    b->cells = (float**)malloc(b->rows*sizeof(float*));

    for (int i = 0; i < matrix->rows; i++) {
        *(matrix->cells+i) = (float*)malloc(matrix->columns*sizeof(float));
        for (int j = 0; j < matrix->columns; j++) {
            if (((i+1)+(j+1))%2 == 0) *(*(matrix->cells+i)+j) = 2*i+j;
            else *(*(matrix->cells+i)+j) = (1+i)*(1+j);
            // if (i == j) *(*(matrix->cells+i)+j) = 1;
            // else *(*(matrix->cells+i)+j) = 0;
        }
    }
    for (int i = 0; i < b->rows; i++) {
        *(b->cells+i) = (float*)malloc(b->columns*sizeof(float));
        for (int j = 0; j < b->columns; j++) {
            *(*(b->cells+i)+j) = (1+i)+(1+j);
        }
    }
    // displayMatrix(b);

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

    Matrix *I = multiply(mult, inv);
    printf("-----------------Indentity-----------------\n");
    displayMatrix(I);
    printf("-----------------END-----------------\n");

    Matrix *LS = multiply(matrix, b);
    printf("-----------------Linear System-----------------\n");
    displayMatrix(LS);
    printf("-----------------END-----------------\n");

    free(matrix);
    free(transp);
    free(mult);
    free(CxM);
    free(inv);
    free(I);
    free(LS);

    matrix = NULL;
    transp = NULL;
    mult = NULL;
    CxM = NULL;
    inv = NULL;
    I = NULL;
    LS = NULL;  

    return 0;
}