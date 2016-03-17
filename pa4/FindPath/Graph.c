/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 4
 */
//-----------------------------------------------------------------------------
// Graph.c
//-----------------------------------------------------------------------------

#include "Graph.h"

/*** Constructors-Destructors ***/
Graph newGraph(int n){

    Graph G;
    G = myMalloc(sizeof(GraphObj));
    G->order = n+1;
    G->adj = myCalloc(G->order, sizeof(List*));
    G->color = myCalloc(G->order, sizeof(COLORS*));
    G->parent = myCalloc(G->order, sizeof(int*));
    G->distance = myCalloc(G->order, sizeof(int*));
    G->size = 0;
    G->source = NIL;

    for(int i = 1; i < G->order; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }

    return G;
}

void freeGraph(Graph* pG){
    if( pG != NULL && *pG != NULL ){
        int i = (*pG)->order-1;
        while( i > 0 ){
            freeList((&(*pG)->adj[i]));
            i--;
        }
        myFree((*pG)->adj);
        myFree((*pG)->color);
        myFree((*pG)->parent);
        myFree((*pG)->distance);
        myFree(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
int getOrder(Graph G){
	return G->order;
}

int getSize(Graph G){
    return G->size;
}

int getSource(Graph G){
    return G->source;
}

int getParent(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: getParent() called on vertex out of bounds.");
		exit(1);
	}
    return G->parent[u];
}

int getDist(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
			printf("Graph Error: getDist() called on vertex out of bounds.");
			exit(1);
		}
    return G->distance[u];
}

// void getPath(List, Graph, Vertex u) //////////////////
// Appends to the List L the vertices of a shortest path
// in G from source to u, or appends to L the value of
// NIL if no such path exists. BFS() must be called
// before getPath()
void getPath(List L, Graph G, int u){
    // if G's source is NIL BFS has not yet been called
    if(getSource(G) == NIL){
        printf("Graph Error: getPath() - BFS() has not yet been called.");
        exit(1);
    }
    // check that u is actually reachable from G's source
    // if not append NIL onto L
    if(getDist(G, u) < 0){
        append(L, NIL);
    }
    // also check if u is the source, in which
    // case just put u onto the list and return
    else if(getDist(G, u) == 0){ append(L, u); }
    // if it is then,
    else {
        // if u's parent is not the source
        // recursively call getPath() on u's
        // parent
        if(getParent(G, u) != getSource(G)){
            getPath(L, G, getParent(G, u));
        }
        // the recursion will collapse upward
        // appending each node in the path,
        // starting with the one closest to the
        // source, onto L
        append(L, u);
        // and prepend the source vertex onto
        // the list. This is only done on the
        // innermost call to getPath() to
        // ensure the source is only added to
        // the list once.
        if(getParent(G, u) == getSource(G)){
            prepend(L, getSource(G));
        }
    }
}
// pre-condition: getSource(G) != NIL

/*** Manipulation procedures ***/

// void makeNULL(Graph) ////////////////////////////////
// deletes all edges of G, restoring it to
// its original (no edge) state.
void makeNull(Graph G){
    for(int i = 1; i < getOrder(G); i++){
        clear(G->adj[i]);
    }
    G->size = 0;
}

// void addEdge(Graph, Vertex u, Vertex v) /////////////
// Inserts a new undirected edge from u to v
// i.e. v is added to the adjacency list of u
// and u is added to the adjacency list of v.
void addEdge(Graph G, int u, int v){
    if( u == v ){
        printf("Graph Error: addEdge() - edge not possible.");
        exit(1);
    }
    // add v to u's adjacency list
    addArc(G, u, v);
    // add u to v's adjacency list
    addArc(G, v, u);
    // correct extra increase in size of G
    // since this is only for undirected
    // graphs
    G->size--;
}

// void addArc(Graph, Vertex u, Vertex v) //////////////
// inserts a new directed edge from u to v
// i.e. v is added to the adjacency
// List of u (but not u to the adjacency List of v).
void addArc(Graph G, int u, int v){
    // check cases where v or u are outside of the bounds of the
    // graph G's order
    if( u < 1 || u > getOrder(G)){
        printf("Graph Error: addArc() - origin vertex out of bounds.");
        exit(1);
    }
    if( v < 1 || v > getOrder(G)){
        printf("Graph Error: addArc() - terminus vertex out of bounds.");
        exit(1);
    }
    // simply add v to u's adjacency list if it is empty
    if(isEmpty(G->adj[u])){ append(G->adj[u], v); G->size++; }
    // otherwise
    else{
        // move u's adjacency list cursor to the first element
        moveTo(G->adj[u], 0 );
        // move down the list until either the cursor falls of the end
        // or the element highlighted is greater than v
        while(getIndex(G->adj[u]) >= 0 && getElement(G->adj[u]) < v){
            moveNext(G->adj[u]);
        }
        // if the cursor fell off the end then tack v onto
        // the end of the list
        if(getIndex(G->adj[u]) < 0){ append(G->adj[u], v); G->size++; }
        // if the above while broke because
        // we found an element greater than
        // v,  then insert v in front of
        // that element
        else if (getElement(G->adj[u]) != v){
            insertBefore(G->adj[u], v);
            G->size++;
        }
    }
}
// pre-condition: 1 <= u,v <= getOrder(G)

// void BFS(Graph, SourceVertex) ///////////////////////
// Performs a Breadth First Search on Graph G
// using s as the source vertex
void BFS(Graph G, int s){
	// check that the graph exists and is not empty
	if(G == NULL || getOrder(G) < 1){
		printf("Graph Error: BFS() called on null or empty graph.");
		exit(1);
	}
	// check that the source vertex is within the order
	// of the graph
	if(s < 1 || s > getOrder(G)){
		printf("Graph Error: BFS() called with source out of bounds.");
		exit(1);
	}

	// declare vertices u and v
	int u, v;
	G->source = s;
	// initialize each adjacency list in G
	// except for the source, s
	for(int i = 1; i < getOrder(G); i++){
		if(i != s){
			G->color[i] = WHITE;
			G->distance[i] = INF;
			G->parent[i] = NIL;
		}
	}
	// color the source GRAY, set its
	// distance to 0, and its parent to
	// NIL
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	// initialize a new list that will
	// serve as our queue
	List list = newList();
	// push the source onto the queue
	append(list, s);
	// while the queue is not empty
	while(!isEmpty(list)){
		// pop the front of the queue off
		// into u
		u = front(list);
		deleteFront(list);
		// check if vertex u has any
		// adjacent vertices
		if(!isEmpty(G->adj[u])){
			// move G's adjacency list for
			// vertex u to the first element
			moveTo(G->adj[u], 0);
			// for each entry in u's adjacency list
			for(int i = 0; i < length(G->adj[u]); i++){
				// get the adjacent vertex into v
				v = getElement(G->adj[u]);
				// if v is WHITE
				if(G->color[v] == WHITE){
					// color it GRAY
					G->color[v] = GRAY;
					// set v's distance to one more than u's
					G->distance[v] = G->distance[u] + 1;
					// set v's parent to u
					G->parent[v] = u;
					// push v onto the back of the queue
					append(list, v);
				}
				// move to the next adjacent vertex
				moveNext(G->adj[u]);
			}
		}
		// we're done with u so color it BLACK
		G->color[u] = BLACK;
	}
	// free the memory used for the queue
	freeList(&list);
}

/*** Other operations ***/
// void printGraph(OutFile, Graph) //////////////////////
// Prints G's adjacency lists to out
void printGraph(FILE* out, Graph G){

    for(int i = 1; i < getOrder(G); i++)
    {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }

    fprintf(out, "\n");
}
