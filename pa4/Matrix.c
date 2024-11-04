// /***
// * Phil Liu
// * phzliu
// * 2024 Fall CSE101 PA4
// * List.h
// * Implements Matrix ADT and its operations
// ***/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"
#include "List.h"

typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

typedef struct MatrixObj {
    int size;
    int NNZ;
    List* row;
} MatrixObj;

typedef struct EntryObj* Entry;

// constructors / destructors

Entry newEntry(int column, double value) {
    Entry E = malloc(sizeof(EntryObj));
    E->column = column;
    E->value = value;
    return E;
}

void freeEntry(Entry* pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->NNZ = 0;
    M->row = calloc(n+1, sizeof(List));
    for (int i = 1; i <= n; i++) {
        M->row[i] = newList();
    }
    return M;
}

void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        Entry e;
        for (int i = 1; i <= size(*pM); i++) {
            moveFront((*pM)->row[i]);
            while (index((*pM)->row[i]) != -1) {
                e = (Entry)get((*pM)->row[i]);
                freeEntry(&e);
                moveNext((*pM)->row[i]);
            }
            freeList(&((*pM)->row[i]));
        }
    free((*pM)->row);
    (*pM)->row = NULL;
    free(*pM);
    *pM = NULL;
    }
}

/*** Access functions ***/

// size() return the size of square Matrix M.
int size(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix error: calling size() on a NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    return M->size;
}

int NNZ(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix error: calling NNZ() on a NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    return M->NNZ;
}
bool equals(Matrix A, Matrix B) {
    if ((A == NULL) || (B == NULL)) {
        fprintf(stderr, "Matrix error: calling equals() on a NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        return false;
    }
    if (NNZ(A) != NNZ(B)) {
        return false;
    }
    Entry entryA;
    Entry entryB;
    for (int i = 1; i <= size(A); i++) {
        if (length(A->row[i]) != length(B->row[i])) {
            return false;
        }

        moveFront(A->row[i]);
        moveFront(B->row[i]);
        while ((index(A->row[i]) != -1) && (index(B->row[i]) != -1)) {
            entryA = (Entry)get(A->row[i]);
            entryB = (Entry)get(B->row[i]);
            if (entryA->column != entryB->column) {
                return false;
            }
            if (entryA->value != entryB->value) {
                return false;
            }
            moveNext(A->row[i]);
            moveNext(B->row[i]);
        }
    }
    return true;
}

/*** Manipulation procedures ***/

void makeZero(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Entry e;
    for (int i = 1; i <= size(M); i++) {
        moveFront(M->row[i]);
        while (index(M->row[i]) != -1) {
            e = (Entry)get(M->row[i]);
            freeEntry(&e);
            moveNext(M->row[i]);
        }
        clear(M->row[i]);
    }
    M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x) { // i = row, j = column, x = value
    if (M == NULL) {
      fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if ((i < 1 || i > M->size) || (j < 1 || j > M->size)) {
      fprintf(stderr, "Matrix Error: changeEntry() called with an invalid index.\n");
      exit(EXIT_FAILURE);
    }

    Entry e;
    moveFront(M->row[i]);
    while (index(M->row[i]) != -1) {
        e = (Entry)get(M->row[i]);

        if (e->column == j) {
            if (x == 0) {
                freeEntry(&e);
                delete(M->row[i]);
                M->NNZ--;
                return;
            }
            else {
                e->value = x;
                return;
            }
        }

        else if (e->column > j) {
            if (x == 0) {
                return;
            }
            else {
                insertBefore(M->row[i], newEntry(j, x));
                M->NNZ++;
                return;
            }
        }
        moveNext(M->row[i]);
    }

    if (x != 0) {
        append(M->row[i], newEntry(j,x));
        M->NNZ++;
    }
}

/*** Matrix Arithmetic operations ***/

Matrix copy(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix B = newMatrix(size(A));
    Entry e;
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->row[i]);
        while (index(A->row[i]) != -1) {
            e = (Entry)get(A->row[i]);
            append(B->row[i], newEntry(e->column, e->value));
            moveNext(A->row[i]);
        }
    }
    B->NNZ = NNZ(A);
    return B;
}

Matrix transpose(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix B = newMatrix(size(A));
    Entry e;
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->row[i]);
        while (index(A->row[i]) != -1) {
            e = (Entry)get(A->row[i]);
            append(B->row[e->column], newEntry(i, e->value));
            moveNext(A->row[i]);
        }
    }
    B->NNZ = NNZ(A);
    return B;
}

Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling scalarMult() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix B = newMatrix(size(A));
    Entry e;
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->row[i]);
        while (index(A->row[i]) != -1) {
            e = (Entry)get(A->row[i]);
            append(B->row[i], newEntry(e->column, x * e->value));
            moveNext(A->row[i]);
            B->NNZ++;
        }
    }
    return B;
}

Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "Matrix Error: calling sum() on matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }

    if (equals(A, B)) {
        return scalarMult(2, A);
    }

    Matrix C = newMatrix(size(A));
    Entry entryA;
    Entry entryB;
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->row[i]);
        moveFront(B->row[i]);

        while (index(A->row[i]) != -1 || index(B->row[i]) != -1) {
            if (index(A->row[i]) != -1 && index(B->row[i]) != -1) {
                entryA = (Entry)get(A->row[i]);
                entryB = (Entry)get(B->row[i]);

                if (entryA->column == entryB->column) {
                    double sum = entryA->value + entryB->value;
                    if (sum != 0) {
                        append(C->row[i], newEntry(entryA->column, sum));
                        C->NNZ++;
                    }
                    moveNext(A->row[i]);
                    moveNext(B->row[i]);
                }
                else if (entryA->column < entryB->column) {
                    append(C->row[i], newEntry(entryA->column, entryA->value));
                    C->NNZ++;
                    moveNext(A->row[i]);
                }
                else {
                    append(C->row[i], newEntry(entryB->column, entryB->value));
                    C->NNZ++;
                    moveNext(B->row[i]);
                }
            }
            else if (index(A->row[i]) != -1) {
                entryA = (Entry)get(A->row[i]);
                append(C->row[i], newEntry(entryA->column, entryA->value));
                C->NNZ++;
                moveNext(A->row[i]);
            }
            else if (index(B->row[i]) != -1) {
                entryB = (Entry)get(B->row[i]);
                append(C->row[i], newEntry(entryB->column, entryB->value));
                C->NNZ++;
                moveNext(B->row[i]);
            }
        }
    }
    return C;
}


Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "Matrix Error: calling diff() on matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }
    if (equals(A, B)) {
        return newMatrix(size(A));
    }

    Matrix C = newMatrix(size(A));
    Entry entryA;
    Entry entryB;
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->row[i]);
        moveFront(B->row[i]);

        while (index(A->row[i]) != -1 || index(B->row[i]) != -1) {
            if (index(A->row[i]) != -1 && index(B->row[i]) != -1) {
                entryA = (Entry)get(A->row[i]);
                entryB = (Entry)get(B->row[i]);

                if (entryA->column == entryB->column) {
                    double diff = entryA->value - entryB->value;
                    if (diff != 0) {
                        append(C->row[i], newEntry(entryA->column, diff));
                        C->NNZ++;
                    }
                    moveNext(A->row[i]);
                    moveNext(B->row[i]);
                }
                else if (entryA->column < entryB->column) {
                    append(C->row[i], newEntry(entryA->column, entryA->value));
                    C->NNZ++;
                    moveNext(A->row[i]);
                }
                else {
                    append(C->row[i], newEntry(entryB->column, -entryB->value));
                    C->NNZ++;
                    moveNext(B->row[i]);
                }
            }
            else if (index(A->row[i]) != -1) {
                entryA = (Entry)get(A->row[i]);
                append(C->row[i], newEntry(entryA->column, entryA->value));
                C->NNZ++;
                moveNext(A->row[i]);
            }
            else if (index(B->row[i]) != -1) {
                entryB = (Entry)get(B->row[i]);
                append(C->row[i], newEntry(entryB->column, -entryB->value));
                C->NNZ++;
                moveNext(B->row[i]);
            }
        }
    }
    return C;
}


double vectorDot(List P, List Q) {
    if ((P == NULL) || (Q == NULL)) {
        fprintf(stderr, "List Error: calling vectorDot() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    double dot = 0.0;
    moveFront(P);
    moveFront(Q);
    Entry e1;
    Entry e2;
    while ((index(P) != -1) && (index(Q) != -1)) {
        e1 = (Entry)get(P);
        e2 = (Entry)get(Q);
        if (e1->column == e2->column) {
            dot += (e1->value * e2->value);
            moveNext(P);
            moveNext(Q);
        }
        else if (e1->column < e2->column) {
            moveNext(P);
        }
        else {
            moveNext(Q);
        }
    }
    return dot;
}

Matrix product(Matrix A, Matrix B) {
    if ((A == NULL) || (B == NULL)) {
        fprintf(stderr, "Matrix Error: calling product() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if (size(A) != size(B)) {
        fprintf(stderr, "Matrix Error: calling product() when Matricies have different sizes\n");
        exit(EXIT_FAILURE);
    }

    double dp;
    Matrix(T) = transpose(B);
    Matrix(C) = newMatrix(size(A));
    for (int i = 1; i <= size(C); i++) {
        if (length(A->row[i]) == 0) {
        }
        else {
            for (int j = 1; j <= size(C); j++) {
                if (length(T->row[j]) != 0) {
                    dp = vectorDot(A->row[i], T->row[j]);
                    if (dp != 0) {
                        append(C->row[i], newEntry(j, dp));
                        C->NNZ++;
                    }
                }    
            }
        }
    }
        
    freeMatrix(&T);
    return C;
}

void printMatrix(FILE* out, Matrix M) {
    if (out == NULL) {
        fprintf(stderr, "Output Error: calling printMatrix() on NULL output\n");
        exit(EXIT_FAILURE);
    }
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Entry e;
    for (int i = 1; i <= size(M); i++) {
        if (length(M->row[i]) > 0) {
            fprintf(out, "%d: ", i);
            moveFront(M->row[i]);
            while (index(M->row[i]) != -1) {
                e = (Entry)get(M->row[i]);
                fprintf(out, "(%d, %.1f) ", e->column, e->value);
                moveNext(M->row[i]);
            }
            fprintf(out, "\n");
        }
    }
}