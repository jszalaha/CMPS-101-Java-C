/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 5
 */
//-----------------------------------------------------------------------------
// FindComponents.c
//-----------------------------------------------------------------------------

#include <string.h>
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){

// VARIABLE DECLARATION ///////////////////////////////////////////

    FILE *in, *out;
    char* token;
    char line[MAX_LEN];
    int x, y;
    Graph G, Gt;
    List stack = newList();

// ERROR CHECKING AND I/O PREP ////////////////////////////////////

    //verifies the correct number of arguments
     if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    //opens the in file and out file
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    //checks that they exist
    if(in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if(out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

// INPUT AND GRAPH CREATION ///////////////////////////////////////

     // get first line and store in x
    fgets(line, MAX_LEN, in);
    token = strtok(line, "\n");
    x = y = atoi(token);
    // create new graph of size x
    G = newGraph(x);

    // verify the 0 0 line hasn't been reached then get next line
    while(x != 0 && y != 0 && fgets(line, MAX_LEN, in) != NULL){
        // store first and second
        // numbers in x and y
        // respectively
        token = strtok(line, " ");
        x = atoi(token);
        token = strtok(NULL, " ");
        y = atoi(token);
        // add a new arc with
        // origin x and terminus y
        if( x != 0 && y != 0){
            addArc(G, x, y);
        }
    }
    // print out G's adjacency list representation
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

// STRONGLY-CONNECTED-COMPONENTS ALGORITHM IMPLEMENTATION ///////////

    // Initialize the stack to contain the vertices
    // of G in ascending order
    for(int i = 1; i < getOrder(G); i++){
        append(stack, i);
    }
    // Run a depth first search on G using stack
    // as the processing order of the vertices,
    // after stack will hold the vertices sorted
    // in order of decreasing finish time
    DFS(G, stack);
    // Create a transpose graph of G
    Gt = transpose(G);
    // Run the depth first search again this time
    // on the transpose of G using the output
    // stack from the first call
    DFS(Gt, stack);
    // the resulting stack contains the strongly
    // connected components of G
    fprintf(out, "G contains %d strongly connected components:", getSCC(Gt));
    // for however many SCC's there are
    for(int i = 1; i <= getSCC(Gt); i++){
        // start at the bottom of the stack
        moveTo(stack, length(stack)-1);
        // move up until you reach a vertex with a
        // NIL parent, that is the root of a SCC
        while(Gt->parent[getElement(stack)] != NIL){
            movePrev(stack);
        }
        // print it as the first in its component list
        fprintf(out, "\nComponent %d: ", i);
        fprintf(out, "%d ", getElement(stack));
        moveNext(stack);
        // and move down the stack printing out vertices
        // until you reach the bottom
        while(getIndex(stack) >= 0){
            fprintf(out, "%d ", getElement(stack));
            moveNext(stack);
        }
        // now move back up the stack deleting as you
        // go until you reach the root of this SCC
        while(Gt->parent[back(stack)] != NIL){
            deleteBack(stack);
        }
        // and delete it
        deleteBack(stack);
    }

// CLEAN UP /////////////////////////////////////////////////////////

    fclose(out);
    fclose(in);

    freeList(&stack);
    stack = NULL;

    freeGraph(&G);
    freeGraph(&Gt);
    G = NULL;
    Gt = NULL;

    return (0);
}
