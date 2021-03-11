#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H

void displayMatrix(float **A, int rows, int columns);
float** transpose(float **m, int row, int column);
float** multiply(float **m1, int row_1, int column_1, float **m2, int row_2, int column_2);
float determinant(float **A, int rows, int columns,  int position);
float** multiplyBy(float **A, int rows, int columns, float constant);
// float** cofactor(float **A, int rows, int columns, int i, int j);

#endif