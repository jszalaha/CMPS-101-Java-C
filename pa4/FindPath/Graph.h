/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 4
 */
//-----------------------------------------------------------------------------
// Graph.h
//-----------------------------------------------------------------------------

#include "List.h"

#define NIL 0
#define INF -1

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

typedef enum COLORS {WHITE, GRAY, BLACK} COLORS;

typedef struct GraphObj{
    List *adj;
    COLORS *color;
    int *parent;
    int *distance;
    int order;
    int size;
    int source;
}GraphObj;

typedef GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);

#endif
