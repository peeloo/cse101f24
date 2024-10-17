/***
* Phil Liu
* phzliu
* 2024 Fall CSE101 PA2
* Graph.c
* Implements Graph ADT and its operations
***/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Graph.h"

// structs --------------------------------------------------------------------

typedef struct GraphObj {
    List *neighbors;
    int *color;
    int *parent;
    int *distance;
    int order;
    int size;
    int source;
} GraphObj;

// constructor/destructor -----------------------------------------------------

Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));

    G->order = n;
    G->size = 0;
    G->source = NIL;

    G->neighbors = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->distance = calloc(n+1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        G->neighbors[i] = newList();
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->color[i] = WHITE;
    }
    return G;
}

void freeGraph(Graph* pG) {
    if ((pG != NULL) && (*pG != NULL)) {
        for (int i = 1; i <= (*pG)->order; i++) {
            freeList(&((*pG)->neighbors[i]));
        }
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free((*pG)->neighbors);
        free(*pG);
        *pG = NULL;
    }
}

// Access functions -----------------------------------------------------------

int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling getOrder() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling getSize() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getSource(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling getSource() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling getParent() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        fprintf(stderr, "Graph error: calling getParent() on invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) != NIL) {
        return G->parent[u];
    }
    return NIL;
}

int getDist(Graph G, int u) {
    if (G == NULL) {
      fprintf(stderr, "Graph error: calling getDist() on NULL graph\n");
      exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        fprintf(stderr, "Graph error: calling getDist() on invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) != NIL) {
        return G->distance[u];
    }
    return INF;
}   

void getPath(List L, Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling getPath() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        fprintf(stderr, "Graph error: calling getDist() on invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        fprintf(stderr, "Graph error: getSource(G) NULL\n");
        exit(EXIT_FAILURE);
    }
    
    if (u == getSource(G)) { 
        append(L, getSource(G));
    }
    else if (getParent(G, u) == NIL) { 
        append(L, NIL);
    }
    else {
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}

// Manipulation procedures ----------------------------------------------------

void makeNull(Graph G) {
    if (G == NULL) {
      fprintf(stderr, "Graph error: calling makeNULL() on NULL graph\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        freeList(&G->neighbors[i]);
    }
    G->size = 0;
}

void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
      fprintf(stderr, "Graph error: calling addEdge() on NULL graph\n");
      exit(EXIT_FAILURE);
    }
    if ((u < 1 || u > getOrder(G)) || (v < 1 || v > getOrder(G))) {
        fprintf(stderr, "Graph error: calling getEdge() on invalid verticies\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling addArc() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph error: calling addArc() with ints out of range\n");
        exit(EXIT_FAILURE);
    }
    if (length(G->neighbors[u]) == 0) {
        append(G->neighbors[u], v);
        G->size++;
    }

    moveFront(G->neighbors[u]);
    while (true) {   
        if (v == get(G->neighbors[u])) {
            break;
        }

        if (v > get(G->neighbors[u])) {
            moveNext(G->neighbors[u]);

            if (index(G->neighbors[u]) < 0) {
                append(G->neighbors[u], v);
                G->size++;
                break;
            }
        } 
        else {
            insertBefore(G->neighbors[u], v);
            G->size++;
            break;
        }
    } 
   
}

void BFS(Graph G, int s) {
    if (G == NULL) {
      fprintf(stderr, "Graph error: calling BFS() on NULL graph\n");
      exit(EXIT_FAILURE);
    }

    G->source = s;
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }

    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;

    List L = newList();
    append(L, s);
    while (length(L) > 0) {
        int x = front(L);
        deleteFront(L);
        moveFront(G->neighbors[x]);
        while (index(G->neighbors[x]) >= 0) {
            int y = get(G->neighbors[x]);
            moveNext(G->neighbors[x]); 
            if (G->color[y] == WHITE) {
                G->color[y] = GRAY;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(L, y);   
            }
        }
        G->color[x] = BLACK;
    }
    freeList(&L);
}

// Other operations -----------------------------------------------------------

void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
      fprintf(stderr, "Graph error: calling printGraph() on NULL graph\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->neighbors[i]);
    }
    fprintf(out, "\n");
}