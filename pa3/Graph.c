/***
* Phil Liu
* phzliu
* 2024 Fall CSE101 PA3
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
    int *discovery;
    int *finish;
    int order;
    int size;
} GraphObj;

// constructor/destructor -----------------------------------------------------

Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));

    G->order = n;
    G->size = 0;

    G->neighbors = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->discovery = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        G->neighbors[i] = newList();
        G->parent[i] = NIL;
        G->color[i] = WHITE;
        G->discovery[i] = UNDEF;
        G->finish[i]= UNDEF;
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
        free((*pG)->neighbors);
        free((*pG)->discovery);
        free((*pG)->finish);
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


int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling getParent() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        fprintf(stderr, "Graph error: calling getParent() on invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling getDiscover() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        fprintf(stderr, "Graph error: calling getDiscover() on invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->discovery[u];
}

int getFinish(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling getDiscover() on NULL graph\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || u > getOrder(G)) {
        fprintf(stderr, "Graph error: calling getDiscover() on invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}

// Manipulation procedures ----------------------------------------------------

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
    if ((u < 1 || u > getOrder(G)) || (v < 1 || v > getOrder(G))) {
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

int Visit(Graph G, int time, int v, List L) {
        G->discovery[v] = ++time;
        G->color[v] = GRAY;
        moveFront(G->neighbors[v]);
        while (index(G->neighbors[v]) != -1) {
                if (G->color[get(G->neighbors[v])] == WHITE) {
                    G->parent[get(G->neighbors[v])] = v;
                    time = Visit(G, time, get(G->neighbors[v]), L);
                }
                    moveNext(G->neighbors[v]);
        }
        G->color[v] = BLACK;
        G->finish[v] = ++time;
	    prepend(L, v);
        return time;
}



void DFS(Graph G, List stack) {
    if (G == NULL || stack == NULL) { 
    fprintf(stderr, "Graph Error: calling DFS() on NULL Graph\n");
    exit(EXIT_FAILURE);
    }

	if (length(stack) != getOrder(G)) {
		fprintf(stderr, "Graph Error: stack length != order of the graph\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= getOrder(G); i++) {
		G->parent[i] = NIL;
		G->color[i] = WHITE;
	}
	int time = 0;
	List initialOrder = copyList(stack);
	clear(stack);
	moveFront(initialOrder); 

	while (index(initialOrder) != -1) {
		if(G->color[get(initialOrder)] == WHITE){
			time = Visit(G, time, get(initialOrder), stack);
		}
		moveNext(initialOrder);
	}
	freeList(&initialOrder);
}

// Other operations -----------------------------------------------------------

Graph transpose(Graph G) {
	int n = getOrder(G);
	Graph T = newGraph(n);
	for(int i = 1; i <= n; i++){
		moveFront(G->neighbors[i]);
		while(index(G->neighbors[i]) >= 0) {
			addArc(T, get(G->neighbors[i]), i);
			moveNext(G->neighbors[i]);
		}
	}
	return T;
}
Graph copyGraph(Graph G){
	int n = getOrder(G);
	Graph cp = newGraph(n);

	for (int i = 1; i <= n; i++) {
		cp->neighbors[i] = copyList(G->neighbors[i]);
		cp->parent[i] = G->parent[i];
		cp->finish[i] = G->finish[i];
		cp->discovery[i] = G->discovery[i];
	}
	return cp;
}

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
