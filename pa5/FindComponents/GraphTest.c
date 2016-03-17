/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 5
 */
//-----------------------------------------------------------------------------
// GraphTest.c
//-----------------------------------------------------------------------------

#include "Graph.h"

int main(int argc, char * argv[]){

    Graph G = newGraph(5);
    List stackG = newList();
    for(int i = 1; i < getOrder(G); i++){
        append(stackG, i);
    }
    Graph H = newGraph(10);
    List stackH = newList();
    for(int i = 1; i < getOrder(H); i++){
        append(stackH, i);
    }

    printf("%d\n", getOrder(G));
    printf("%d\n", getOrder(H));
    printf("%d\n", getSize(G));
    printf("%d\n", getSize(G));
    printList(stdout, stackG);
    printf("\n");
    printList(stdout, stackH);
    printf("\n");

    for(int i = 1; i < getOrder(G)-1; i++){
        addArc(G, i, i+1);
        printf("%d\n", getSize(G));
    }
    printf("%d\n", getSize(G));

    printf("%d\n", getSize(H));
    for(int i = 1; i < getOrder(H)-2; i++){
        addArc(H, i, i+1);
        addArc(H, i, i+2);
    }
    printf("%d\n", getSize(H));

    printf("%d\n", getParent(G, 5));
    printf("%d\n", getDiscover(G, 5));
    printGraph(stdout, G);

    printf("%d\n", getParent(H, 10));
    printf("%d\n", getDiscover(H, 10));
    printGraph(stdout, H);

    DFS(G, stackG);
    printf("%d\n", getParent(G, 5));
    printf("%d\n", getDiscover(G, 5));
    printf("%d\n", getFinish(G, 5));

    printList(stdout, stackG);

    Graph Gt = transpose(G);

    printf("\n");
    printGraph(stdout, Gt);

    DFS(Gt, stackG);

    printList(stdout, stackG);

    DFS(H, stackH);
    printf("\n");
    printf("%d\n", getParent(H, 10));
    printf("%d\n", getDiscover(H, 10));
    printf("%d\n", getFinish(H, 10));
    printf("%d\n", getParent(H, 8));
    printf("%d\n", getParent(H, 6));
    printf("%d\n", getParent(H, 5));

    printList(stdout, stackH);

    Graph Ht = transpose(H);

    printf("\n");
    printGraph(stdout, Ht);

    DFS(Ht, stackH);

    printList(stdout, stackH);

    freeGraph(&G);
    freeGraph(&H);
    freeGraph(&Ht);
    freeGraph(&Gt);
    freeList(&stackG);
    freeList(&stackH);

    return 0;
}
/*
    Expected Output:

    6
    11
    0
    0
    1 2 3 4 5
    1 2 3 4 5 6 7 8 9 10
    1
    2
    3
    4
    4
    0
    16
    0
    -1
    1: 2
    2: 3
    3: 4
    4: 5
    5:

    0
    -1
    1: 2 3
    2: 3 4
    3: 4 5
    4: 5 6
    6: 6 7
    7: 8 9
    8: 9 10
    9:
    10:

    4
    5
    6
    1 2 3 4 5
    1:
    2: 1
    3: 2
    4: 3
    5: 4

    5 4 3 2 1
    8
    11
    12
    7
    5
    4
    1 2 3 4 5 6 7 8 10 9
    1:
    2: 1
    3: 1 2
    4: 2 3
    5: 3 4
    6: 4 5
    7: 5 6
    8: 6 7
    9: 7 8
    10: 8

    9 10 8 7 6 5 4 3 2 1
*/

