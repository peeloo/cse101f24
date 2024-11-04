/***
 * Phil Liu
 * phzliu
 * 2024 Fall CSE101 PA4
 * MatrixTest.c
 * Test file for Matrix ADT
 ***/

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main() {
    // Create matrices for testing
    Matrix A = newMatrix(4);
    Matrix B = newMatrix(4);

    // Test size() and NNZ()
    printf("Size of A: %d\n", size(A));
    printf("Initial non-zero count in A: %d\n", NNZ(A));

    // Test changeEntry() and NNZ()
    changeEntry(A, 1, 1, 5.0);
    changeEntry(A, 2, 2, 3.2);
    changeEntry(A, 3, 3, -4.5);
    changeEntry(B, 1, 1, 5.0);
    changeEntry(B, 2, 2, 1.5);
    changeEntry(B, 3, 4, 7.8);

    printf("Non-zero count in A after insertions: %d\n", NNZ(A));
    printf("Non-zero count in B after insertions: %d\n", NNZ(B));

    // Test printMatrix()
    printf("Matrix A:\n");
    printMatrix(stdout, A);
    printf("Matrix B:\n");
    printMatrix(stdout, B);

    // Test equals()
    printf("Are A and B equal? %s\n", equals(A, B) ? "Yes" : "No");

    // Test copy()
    Matrix C = copy(A);
    printf("Matrix C (copy of A):\n");
    printMatrix(stdout, C);
    printf("Are A and C equal? %s\n", equals(A, C) ? "Yes" : "No");

    // Test scalarMult()
    Matrix D = scalarMult(2.0, A);
    printf("Matrix D (2 * A):\n");
    printMatrix(stdout, D);

    // Test sum()
    Matrix E = sum(A, B);
    printf("Matrix E (A + B):\n");
    printMatrix(stdout, E);

    // Test diff()
    Matrix F = diff(A, B);
    printf("Matrix F (A - B):\n");
    printMatrix(stdout, F);

    // Test transpose()
    Matrix G = transpose(A);
    printf("Matrix G (transpose of A):\n");
    printMatrix(stdout, G);

    // Test product()
    Matrix H = product(A, B);
    printf("Matrix H (A * B):\n");
    printMatrix(stdout, H);

    // Test makeZero()
    makeZero(A);
    printf("Matrix A after makeZero():\n");
    printMatrix(stdout, A);
    printf("Non-zero count in A after makeZero(): %d\n", NNZ(A));

    // Free all matrices
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);

    return 0;
}
