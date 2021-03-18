#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "neural.h"

int main(int argc, char **argv)
{
    Matrix *output = (Matrix*)malloc(sizeof(Matrix));
    output->rows = 1;
    output->columns = 1;
    output->cells = (float**)malloc(sizeof(float*));
    *output->cells = (float*)malloc(sizeof(float));
    **output->cells = 2;

    Matrix *output_expected = (Matrix*)malloc(sizeof(Matrix));
    output_expected->rows = 1;
    output_expected->columns = 1;
    output_expected->cells = (float**)malloc(sizeof(float*));
    *output_expected->cells = (float*)malloc(sizeof(float));
    **output_expected->cells = 4;

    Network *NN = CreateNetwork();
    NN->add(NN, 4,3);
    // NN->add(NN, 3,3);
    NN->add(NN, 3,2);
    NN->add(NN, 2,1);
    // displayNetwork(NN->L);

    // Matrix *A = fowardPropagation(NN->L);
    // printf("%dx%d\n", A->rows, A->columns);
    // displayMatrix(A);

    calcErrors(NN->L, output_expected, output);
    // displayNetwork(NN->L);

    free(NN);
    NN = NULL;

    return 0;
}