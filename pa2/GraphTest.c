/***
* Phil Liu
* phzliu
* 2024 Fall CSE101 PA2
* GraphTest.c
* Test client for Graph ADT
***/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main() {
    int n = 6; // Number of vertices

    // Step 1: Create a new graph with n vertices
    Graph G = newGraph(n);

    // Step 2: Add edges to the graph (undirected edges)
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);

    // Step 3: Add an arc to the graph (directed edge)
    addArc(G, 6, 3);

    // Step 4: Print the graph (adjacency list representation)
    printf("Graph G adjacency list:\n");
    printGraph(stdout, G);

    // Step 5: Run BFS on the graph starting from vertex 1
    BFS(G, 1);
    
    // Step 6: Check BFS properties
    printf("\nResults of BFS starting from vertex 1:\n");
    for (int i = 1; i <= n; i++) {
        printf("Vertex %d: parent = %d, distance = %d\n", i, getParent(G, i), getDist(G, i));
    }

    // Step 7: Find and print the path from source (1) to each vertex
    printf("\nPaths from vertex 1 to others:\n");
    List path = newList();
    for (int i = 1; i <= n; i++) {
        getPath(path, G, i);
        printf("Path from 1 to %d: ", i);
        if (front(path) == NIL) {
            printf("No path\n");
        } else {
            printList(stdout, path);
            printf("\n");
        }
        clear(path); // Clear list for the next path
    }

    // Step 8: Check graph properties (order, size, source)
    printf("\nGraph properties:\n");
    printf("Order (number of vertices): %d\n", getOrder(G));
    printf("Size (number of edges): %d\n", getSize(G));
    printf("Source vertex from BFS: %d\n", getSource(G));

    // Step 9: Reset the graph using makeNull
    makeNull(G);

    // Step 10: Free memory
    freeList(&path);
    freeGraph(&G);

    return 0;
}
