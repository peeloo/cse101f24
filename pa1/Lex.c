/***
* Phil Liu
* phzliu
* 2024 Fall CSE101 PA1
* Lex.c
* Reads from input file and returns words lexicographically sorted
***/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"
#define BUFFER_LEN 512

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Use ./Lex <input> <output>");
        exit(EXIT_FAILURE);
    }

    FILE *input, *output; 
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    if (input == NULL) {
        fprintf(stderr, "Input is NULL");
        exit(EXIT_FAILURE);
    }
    if (output == NULL) {
        fprintf(stderr, "Output is NULL");
        exit(EXIT_FAILURE);
    }

    int numLines = 0;
    char buffer[BUFFER_LEN];
    while (fgets(buffer, sizeof(buffer), input) != NULL) {
        numLines++;
    }

    char **inputWords;
    inputWords = (char **)malloc(numLines * sizeof(char *));
    if (inputWords == NULL) {
        fprintf(stderr, "Memory allocation for string array failed.\n");
        exit(EXIT_FAILURE);
    }

    rewind(input);

    for (int i = 0; i < numLines; i++) {
        if (fgets(buffer, BUFFER_LEN, input) != NULL) {
            inputWords[i] = (char *)malloc(sizeof(buffer));
            if (inputWords[i] == NULL) {
                fprintf(stderr, "Memory allocation for string failed.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(inputWords[i], buffer);
        }
    }
    
    List sorted = newList();
    
    for (int i = 0; i < numLines; i++) {
        if (length(sorted) == 0) {
            append(sorted, i);
        }
        else {
            moveFront(sorted);
            while (index(sorted) != -1 && strcmp(inputWords[i], inputWords[get(sorted)]) > 0) {
                moveNext(sorted);
            }
            if (index(sorted) == -1) {
                append(sorted, i);
            } 
            else {
                insertBefore(sorted, i);
            }
        }
    }

    moveFront(sorted);
    while (index(sorted) != -1) {
        fprintf(output, "%s", inputWords[get(sorted)]);
        moveNext(sorted);
    }

    for (int i = 0; i < numLines; i++) {
        free(inputWords[i]);
    }
    free(inputWords);
    freeList(&sorted);

    fclose(input);
    fclose(output);

    return 0;
}
