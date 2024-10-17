/***
* Phil Liu
* phzliu
* 2024 Fall CSE101 PA2
* FindPath.c
* Finds shortest paths between pairs of verticies
***/

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./FindPath <input file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "Unable to open input\n");
        exit(EXIT_FAILURE);
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        fprintf(stderr, "Unable to open output\n");
        exit(EXIT_FAILURE);
    }

    int num_verticies;
    fscanf(input, "%d", &num_verticies);
    Graph G = newGraph(num_verticies);

    int u, v;
    while (fscanf(input, "%d %d \n", &u, &v) && (u != 0)) {
        addEdge(G, u, v);
    }
    printGraph(output, G);

    while (fscanf(input, "%d %d \n", &u, &v) && (u != 0)) {
        BFS(G, u);
        List L = newList();
        if (getDist(G, v) == INF) {
            fprintf(output, "The distance from %d to %d is infinity\n", u, v);
            fprintf(output, "No %d-%d path exists\n", u, v);
            fprintf(output, "\n");
        } else {
            getPath(L, G, v);
            fprintf(output, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
            fprintf(output, "A shortest %d-%d path is: ", u, v);
            printList(output, L);
            fprintf(output, "\n");
        }
        freeList(&L);

    }

    makeNull(G);
    freeGraph(&G);
    fclose(input);
    fclose(output);
}