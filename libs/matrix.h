#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H

typedef struct  {
    int rows;
    int columns;
    float **cells;
} Matrix;

void displayMatrix(Matrix *A);
Matrix* transpose(Matrix *m);
Matrix* multiply(Matrix *A, Matrix *B);
float determinant(Matrix *A, int position);
Matrix* multiplyBy(Matrix *A, float constant);
Matrix* inverse(Matrix *A);
Matrix* SolveSystem(Matrix *A, Matrix *B);

#endif