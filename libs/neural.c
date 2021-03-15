#include "neural.h"
#include "matrix.h"

#include <stdlib.h>
#include <stdio.h>

void displayLayers(Layer *L)
{
    printf("------------------Layer %d------------------\n", L->layer);
    for (int i = 0; i < L->W->rows; i++) {
        for (int j = 0; j < L->W->columns; j++) {
            printf("%.2f ", *(*(L->W->cells+i)+j));
        }
        printf("\n");
    }
    printf("-------------------------------------------\n");
}

void displayNetwork(Layer *L)
{
    displayLayers(L);
    displayNetwork(L->next);
}

void initializeNeurons(Matrix *A, int row, int column)
{
    if (row == 0) return;
    else if (column == 0) initializeNeurons(A, row-1, A->columns);
    else {
        if (A->cells == NULL) A->cells = (float**)malloc(A->rows*sizeof(float*));
        if (*(A->cells+row-1) == NULL) *(A->cells+row-1) = (float*)malloc(A->columns*sizeof(float));
        *(*(A->cells+row-1)+column-1) = 1;
        initializeNeurons(A, row, column-1);
    }
}

Layer* createLayer(int input, int output)
{
    Layer *L = (Layer*)malloc(sizeof(Layer));
    L->layer = 0;
    L->next = NULL;
    L->before = NULL;
    L->W = (Matrix*)malloc(sizeof(Matrix));
    L->W->rows = input;
    L->W->columns = output;
    initializeNeurons(L->W, L->W->rows, L->W->columns);

    return L;
}

void lastLayer(Layer *L, int input, int output)
{
    if (L->next != NULL) lastLayer(L->next, input, output);
    else {
        L->next = createLayer(input, output);
        L->next->before = L;
        L->next->layer = L->layer + 1;
    }
    // displayMatrix(L->next->W);
}

void addLayer(Network *this, int input, int output)
{
    if (this->L == NULL) this->L = createLayer(input, output);
    else lastLayer(this->L, input, output);
    this->layers++;
}

Network* CreateNetwork()
{
    Network *NN = (Network*)malloc(sizeof(Network));
    NN->layers = 0;
    NN->add = addLayer;

    return NN;
}

Matrix* fowardPropagation(Layer *L)
{
    if (L->next == NULL) return transpose(L->W);
    else return multiply(fowardPropagation(L->next), transpose(L->W));
}

Matrix* fowardPropagation2(Layer *L)
{
    Matrix *W = transpose(L->W);
    while (L->next != NULL) {
        W = multiply(transpose(L->next->W), W);
        L = L->next;
    }
    return W;
}