#ifndef NEURAL_LIB_H
#define NEURAL_LIB_H

#include "matrix.h"

typedef struct Layer {
    int layer;
    struct Layer *next;
    struct Layer *before;
    Matrix *W;
} Layer;

typedef struct Network {
    int layers;
    Layer *L;
    void (*add)(struct Network *this, int input, int output);
} Network;

Network* CreateNetwork();
void addLayer(Network *N, int input, int output);
void displayNetwork(Layer *L);
Matrix* fowardPropagation(Layer *L);

#endif