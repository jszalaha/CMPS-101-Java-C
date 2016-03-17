/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 4
 */
//-----------------------------------------------------------------------------
//  README
//-----------------------------------------------------------------------------

-Graph.h-
The header file containing all prototypes for Graph.c

-Graph.c-
This is a Graph ADT that uses an array of Lists to create an adjacency list 
representation of a graph of n vertices with edges specified by the input file.
It also contains the function of performing a Breadth First Search, using a 
designated source vertex, that assigns each vertex in the graph with a parent 
vertex and a distance from the source. It then, with this info, finds a single 
shortest path between any vertex in the graph and the designated source.

-GraphTest.c-
A basic test file for the graph ADT.

-FindPath.c-
The main client. This takes input from a text file entered on the command line 
as the first argument after the executable. It then uses the Graph and List
ADTs to form an adjacency list representation of the graph specified by the 
input. It then calls a Breadth First Search operation for each source listed 
in the file and prints out the shortest path and distance to a given vertex 
coupled with each listed source in the input file. All BFS calls are processed 
in ascending vertex label order.

-List.h-
The header file containing all prototypes for List.c

-List.c-
This is a doubly linked List ADT that includes a "cursor" for navigating list 
nodes. This ADT is used by Graph.c to implement an adjacency list 
representation of the input graph as well as create a queue for the purpose of 
performing a Breadth First Search on the vertices of said graph.

-Makefile-
Used to compile the above .h and .c files and create an executable .exe file 
called FindPath. Also contains a clean utility that deletes all object files 
and the created .exe file from the current directory.

-README-