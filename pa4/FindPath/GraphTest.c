/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 4
 */
//-----------------------------------------------------------------------------
// GraphTest.c
//-----------------------------------------------------------------------------

#include "Graph.h"

int main(int argc, char * argv[]){

    List path = newList();

    Graph G = newGraph(5);
    Graph H = newGraph(10);

    printf("%d\n", getOrder(G));
    printf("%d\n", getOrder(H));
    printf("%d\n", getSize(G));

    for(int i = 1; i < getOrder(G)-1; i++){
        addEdge(G, i, i+1);
        printf("%d\n", getSize(G));
    }
    printf("%d\n", getSize(G));

    printf("%d\n", getSize(H));
    for(int i = 1; i < getOrder(H)-2; i++){
        addEdge(H, i, i+1);
        addEdge(H, i, i+2);
    }
    printf("%d\n", getSize(H));

    printf("%d\n", getSource(G));
    printf("%d\n", getParent(G, 5));
    printf("%d\n", getDist(G, 5));
    printGraph(stdout, G);

    printf("%d\n", getSource(H));
    printf("%d\n", getParent(H, 10));
    printf("%d\n", getDist(H, 10));
    printGraph(stdout, H);

    BFS(G, 1);
    printf("%d\n", getSource(G));
    printf("%d\n", getParent(G, 5));
    printf("%d\n", getDist(G, 5));

    getPath(path, G, 5);
    printList(stdout, path);

    clear(path);
    printList(stdout, path);

    BFS(H, 5);
    printf("\n");
    printf("%d\n", getSource(H));
    printf("%d\n", getParent(H, 10));
    printf("%d\n", getDist(H, 10));
    printf("%d\n", getParent(H, 8));
    printf("%d\n", getParent(H, 6));
    printf("%d\n", getParent(H, 5));

    getPath(path, H, 10);
    printList(stdout, path);

    makeNull(G);
    makeNull(H);
    printf("%d\n", getSize(G));
    printf("%d\n", getSize(H));

    freeGraph(&G);
    freeGraph(&H);
    freeList(&path);

    printf("globalAlloc = %d\n", globalAlloc);

    return 0;
}
/*
    Expected Output:
    6
    11
    0
    1
    2
    3
    4
    4
    0
    16
    0
    0
    -1
    1: 2
    2: 1 3
    3: 2 4
    4: 3 5
    5: 4

    0
    0
    -1
    1: 2 3
    2: 1 3 4
    3: 1 2 4 5
    4: 2 3 5 6
    5: 3 4 6 7
    6: 4 5 7 8
    7: 5 6 8 9
    8: 6 7 9 10
    9: 7 8
    10: 8

    1
    4
    4
    1 2 3 4 5
    5
    8
    3
    6
    5
    0
    5 6 8 10 0
    0
*/
