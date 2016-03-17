/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 4
 */
//-----------------------------------------------------------------------------
// FindPath.c
//-----------------------------------------------------------------------------

#include <string.h>
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

    FILE *in, *out;
    char* token;
    char line[MAX_LEN];
    int x, y;
    Graph G;
    List path = newList();

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
        // add a new edge with
        // vertices x and y
        if( x != 0 && y != 0){
            addEdge(G, x, y);
        }
    }
    // print out G's adjacecy list representation
    printGraph(out, G);
    // reset x and y
    x = -1;
    y = -1;
    // get next line after the 0 0 break
    while(fgets(line, MAX_LEN, in) != NULL && x != 0 && y != 0){
        // store first and second
        // numbers in x and y
        // respectively
        token = strtok(line, " \n");
        x = atoi(token);
        token = strtok(NULL, " \n");
        y = atoi(token);
        // perform a Breadth First Search on G with x
        // as the source vertex
        if( x != 0 && y != 0){
            BFS(G, x);
            // check that y is reachable from x
            // if not print out infinite distance
            // and non-existence of path
            if(getDist(G, y) < 0){
                fprintf(out, "The distance from %d to %d is infinity\n", getSource(G), y);
                fprintf(out, "No %d-%d path exists\n", getSource(G), y);
                fprintf(out, "\n");
            }
            // print out the distance and shortest path from source x
            // to vertex y
            else {
                getPath(path, G, y);
                fprintf(out, "The distance from %d to %d is %d\n", getSource(G), y, getDist(G, y));
                fprintf(out, "A shortest %d-%d path is: ", getSource(G), y);
                printList(out, path);
                fprintf(out, "\n\n");
                clear(path);
            }
        }
    }

    fclose(out);
    fclose(in);

    freeList(&path);
    path = NULL;

    freeGraph(&G);
    G = NULL;

    return (0);
}
