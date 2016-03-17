/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 5
 */
//-----------------------------------------------------------------------------
// Graph.h
//-----------------------------------------------------------------------------

#include "List.h"

#define NIL 0
#define UNDEF -1

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

typedef enum COLORS {WHITE, GRAY, BLACK} COLORS;

typedef struct GraphObj{
    List *adj;
    COLORS *color;
    int *parent;
    int *discover;
    int *finish;
    int order;
    int size;
    int scc;
}GraphObj;

typedef GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
int getSCC(Graph G);

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
void Visit(Graph G, List S, int u, int* t);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif

