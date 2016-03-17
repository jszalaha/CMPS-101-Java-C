/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 3
 */
//-----------------------------------------------------------------------------
//  README
//-----------------------------------------------------------------------------

-Sparse.java-
This class functions as the I/O manager of the file arguments. It reads in all 
information from the first file argument and creates two sparse matrices from 
that information using the Matrix ADT. It then calls several arithmetic 
operations defined in Matrix.java using the two matrices and writes the results 
to the second file argument.

-Matrix.java-
This functions as an ADT built from an array of Lists using List.java that 
serves as a representation of a large n x n sparse matrix. It contains several 
methods for performing arithmetic operations on one or two sparse matrices. The
efficiency of its routines is entirely based on the precondition that the 
matrices being represented are indeed sparse.

-List.java-
This is a doubly linked List ADT that includes a "cursor" for navigating list 
nodes. This ADT is used by Matrix.java to create list array representations of
sparse matrices.

-ListTest.java-
A test client for the List ADT.

-MatrixTest.java-
A test client for the Matrix ADT.

-Makefile-
Used to compile the above .java files and create an executable .jar file called 
Sparse. Also contains a clean utility that deletes all class files and the created 
.jar file from the current directory.

-README-