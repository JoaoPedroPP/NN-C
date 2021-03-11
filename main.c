#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

int main(int argc, char **argv)
{
    int row = 3;
    int column = 3;
    float **matrix = (float**)malloc(row*sizeof(float*));

    for (int i = 0; i < row; i++) {
        *(matrix+i) = (float*)malloc(column*sizeof(float));
        for (int j = 0; j < column; j++) {
            if (((i+1)+(j+1))%2 == 0) *(*(matrix+i)+j) = 2*i+j;
            else *(*(matrix+i)+j) = (1+i)*(1+j);
        }
    }

    // Show matrix
    printf("-----------------Matrix-----------------\n");
    displayMatrix(matrix, row, column);
    printf("-----------------END-----------------\n");

    float **transp = transpose(matrix, row, column);
    printf("-----------------Transpose-----------------\n");
    displayMatrix(transp, column, row);
    printf("-----------------END-----------------\n");

    float **mult = multiply(matrix, row, column, transp, column, row);
    printf("-----------------Multiply-----------------\n");
    displayMatrix(mult, row, row);
    printf("-----------------END-----------------\n");

    float det = determinant(mult, 3, 3, 3);
    printf("-----------------Multiply-----------------\n");
    printf("%.2f\n", det);
    printf("-----------------END-----------------\n");

    free(matrix);
    free(transp);
    free(mult);

    matrix = NULL;
    transp = NULL;
    mult = NULL;

    return 0;
}