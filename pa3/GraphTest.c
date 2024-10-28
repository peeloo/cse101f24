/***
* Phil Liu
* phzliu
* 2024 Fall CSE101 PA3
* GraphTest.c
* A client program to test the Graph ADT functionality.
***/

#include <stdio.h>
#include "Graph.h"

int main() {
    int n = 6; // Number of vertices
    Graph G = newGraph(n); // Create a graph with 6 vertices

    // Testing getOrder and getSize on a new graph
    printf("Graph order: %d (expected: %d)\n", getOrder(G), n);
    printf("Graph size: %d (expected: 0)\n", getSize(G));

    // Add edges and arcs
    addEdge(G, 1, 2);
    addEdge(G, 1, 5);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addArc(G, 5, 6);

    // Print the graph structure
    printf("Graph G after adding edges and arcs:\n");
    printGraph(stdout, G);

    // Check size after adding edges and arcs
    printf("Graph size: %d (expected: 6)\n", getSize(G));

    // Testing DFS and other access functions
    List S = newList();
    for (int i = 1; i <= n; i++) append(S, i);

    DFS(G, S);

    printf("\nDFS finished on G:\n");
    for (int i = 1; i <= n; i++) {
        printf("Vertex %d: parent = %d, discover = %d, finish = %d\n",
               i, getParent(G, i), getDiscover(G, i), getFinish(G, i));
    }

    // Testing transpose and copy functions
    Graph T = transpose(G);
    printf("\nTranspose of G:\n");
    printGraph(stdout, T);

    Graph C = copyGraph(G);
    printf("\nCopy of G:\n");
    printGraph(stdout, C);

    // Clean up memory
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);

    return 0;
}
