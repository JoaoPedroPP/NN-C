#include <stdlib.h>
#include <stdio.h>

// #include "matrix.h"
#include "neural.h"

int main(int argc, char **argv)
{
    Network *NN = CreateNetwork();
    NN->add(NN, 4,3);
    NN->add(NN, 3,2);
    NN->add(NN, 2,1);
    displayNetwork(NN->L);

    return 0;
}