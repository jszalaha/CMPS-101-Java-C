
/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 5
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
    G->discover = myCalloc(G->order, sizeof(int*));
    G->finish = myCalloc(G->order, sizeof(int*));
    G->size = 0;
    G->scc = 0;

    for(int i = 1; i < G->order; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
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
        myFree((*pG)->discover);
        myFree((*pG)->finish);
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

int getSCC(Graph G){
    return G->scc;
}

int getParent(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: getParent() called on vertex out of bounds.");
		exit(1);
	}
    return G->parent[u];
}

int getDiscover(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
		printf("Graph Error: getDiscover() called on vertex out of bounds.");
		exit(1);
	}
	return G->discover[u];
}

int getFinish(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
		printf("Graph Error: getFinish() called on vertex out of bounds.");
		exit(1);
	}
	return G->finish[u];
}

/*** Manipulation procedures ***/

// void addEdge(Graph, Vertex u, Vertex v) /////////////
// Inserts a new bidirectional edge from u to v
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

// void DFS(Graph, List) ///////////////////////////////
// performs a Depth First Search on a Graph using the
// List as the order in which it visits the vertices.
// The output of the List is the same vertex set in
// order of decreasing finish time.
void DFS(Graph G, List S){
    // initialize the time variable
    int time = 0;
    int u;
    // initialize the vertex set of G
    for(int i = 1; i < getOrder(G); i++){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    // set S's list cursor to the last
    // element in the list to serve as
    // the top of our finish time stack
    moveTo(S, length(S)-1);
    // process each vertex in G by the
    // order dictated by S, deleting as
    // it goes
    while(front(S) != getElement(S)){
        u = front(S);
        if(G->color[u] == WHITE){
            Visit(G, S, u, &time);
            G->scc++;
        }
        deleteFront(S);
    }
    // processes the last vertex,
    // highlighted by the cursor
    u = front(S);
    if(G->color[u] == WHITE){
        Visit(G, S, u, &time);
        G->scc++;
    }
    deleteFront(S);
}

// void Visit(Graph, int) ///////////////////////////////
// recursive helper function for DFS()
void Visit(Graph G, List S, int u, int* t){

    int v;
    // discover the vertex u by setting its
    // discover time and coloring it gray
    G->discover[u] = ++(*t);
    G->color[u] = GRAY;
    // given u has adjacent vertices
    if(!isEmpty(G->adj[u])){
        // start with the first element
        // in the adjacency list
        moveTo(G->adj[u], 0);
        // as long as the cursor doesn't
        // fall off the end
        while(getIndex(G->adj[u]) >= 0){
            // get the adjacent vertex
            v = getElement(G->adj[u]);
            // if it is undiscovered
            if(G->color[v] == WHITE){
                // set its parent as u
                G->parent[v] = u;
                // and visit it
                Visit(G, S, v, t);
            }
            // move to the next
            // adjacent vertex
            moveNext(G->adj[u]);
        }
    }
    // at this point we are done with u
    // so we color it black
    G->color[u] = BLACK;
    // set its finish time
    G->finish[u] = ++(*t);
    // and push it onto the stack
    insertAfter(S, u);
}

/*** Other operations ***/

// Graph transpose(Graph) //////////////////////////////
// returns the transpose of the graph passed in
// (all edges' directions are reversed)
Graph transpose(Graph G){
    // creates new empty transpose graph
    Graph trans = newGraph(getOrder(G)-1);
    // for each vertex in G
    for(int i = 1; i < getOrder(G); i++){
        // start at the first element in i's
        // adjacency list
        moveTo(G->adj[i], 0);
        // while the cursor doesn't fall of the end
        while(getIndex(G->adj[i]) >= 0){
            // add a new arc to the transpose graph
            // with the element highlighted in the
            // ith adjacency list of G as origin and
            // vertex i as terminus
            addArc(trans, getElement(G->adj[i]), i);
            moveNext(G->adj[i]);
        }
    }
    return trans;
}

// Graph copyGraph(Graph) ///////////////////////////////
// returns a copy of the graph passed in
Graph copyGraph(Graph G){

    Graph copy = newGraph(getOrder(G));

    for(int i = 1; i < getOrder(G); i++){
        copy->adj[i] = copyList(G->adj[i]);
    }
    copy->size = G->size;

    return copy;
}

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
