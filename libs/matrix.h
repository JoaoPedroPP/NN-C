#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H

typedef struct  {
    int rows;
    int columns;
    float **cells;
} Matrix;

void displayMatrix(Matrix *A);
Matrix* transpose(Matrix *m);
float** multiply(float **m1, int row_1, int column_1, float **m2, int row_2, int column_2);
float determinant(float **A, int rows, int columns,  int position);
float** multiplyBy(float **A, int rows, int columns, float constant);
float **inverse(float **A, int rows, int columns);
// float** cofactor(float **A, int rows, int columns, int i, int j);

#endif