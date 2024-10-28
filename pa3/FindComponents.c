/***
* Phil Liu
* phzliu
* 2024 Fall CSE101 PA3
* FindComponents.c
* Finds strongly connected components given a graph
***/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "Graph.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *in, *out;

    in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    int order = 0;
    fscanf(in, "%d", &order);
    Graph G = newGraph(order);

    int x = 0;
    int y = 0;
    fscanf(in, "%d %d\n", &x, &y);
    while(x != 0 && y != 0) {
        addArc(G, x, y);
        fscanf(in, "%d %d\n", &x, &y);
    }

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    List L = newList();
    for (int i = 1; i <= getOrder(G); i++) {
        append(L, i);
    }

    DFS(G, L);
    Graph T = transpose(G);
    DFS(T, L);

    int num_components = 0;
    moveBack(L);
    while (index(L) != -1) {
        if (getParent(T, get(L)) == NIL) {
            num_components++;
        }
        movePrev(L);
    }
    fprintf(out, "\nG contains %d strongly connected components:\n", num_components);

    int count = 0;
    List *components = calloc(num_components, sizeof(List));
    for (int i = 0; i < num_components; i++) {
        components[i] = newList();
    }

    moveBack(L);
    while (index(L) != -1) {
        prepend(components[count], get(L));
        if (getParent(T, get(L)) == NIL) {
            count++;
        }
        movePrev(L);
    }

    for (int i = 0; i < num_components; i++) {
        fprintf(out,"Component %d: ", i + 1);
        printList(out, components[i]);
        fprintf(out,"\n");
        freeList(&components[i]);
    }

    free(components);
    freeList(&L);
    freeGraph(&G);
    freeGraph(&T);
    fclose(in);
    fclose(out);
    return 0;
}
