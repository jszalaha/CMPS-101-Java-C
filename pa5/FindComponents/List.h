/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 5
 */
//-----------------------------------------------------------------------------
// List.h
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

int globalAlloc;

void* myMalloc(size_t t);
void* myCalloc(size_t s, size_t t);
void myFree(void* t);

// structs --------------------------------------------------------------------
// private NodeObj type
typedef struct NodeObj
{
   int data;
   struct NodeObj* next;
   struct NodeObj* previous;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;

   Node cursor;
   int index;
   int length;
} ListObj;

// private List type
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------
List newList(void);
void freeList(List* pL);
Node newNode(int data);
void freeNode(Node* pN);

// Access functions -----------------------------------------------------------
int length(List L);
int getIndex(List L);
int front(List L);
int back(List L);
int getElement(List L);
int equals(List A, List B);
int isEmpty(List L);

// Manipulation procedures ----------------------------------------------------
void clear(List L);
void moveTo(List L, int i);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);

#endif

