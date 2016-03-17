/*
 * Jordan Zalaha
 * ID: 1438462
 * Programming Assignment 5
 */
//-----------------------------------------------------------------------------
// List.c
//-----------------------------------------------------------------------------

#include "List.h"

#define MAX_LEN 160

void* myMalloc(size_t t)
{
    globalAlloc++;    //global counter
    void*p = malloc(t);
    if(p==NULL) printf("error: can not allocate");
    return p;
}

void* myCalloc(size_t s, size_t t)
{
    globalAlloc += s;
    void*p = calloc(s, t);
    if(p==NULL) printf("error: can not allocate");
    return p;
}
void myFree(void* t)
{
    if(t == NULL)   printf(".,.,.,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,ERROR");
    globalAlloc--; //global counter
    free(t);
}

// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object
List newList(void)
{
	 List L;
	 L = myMalloc(sizeof(ListObj));
	 L->front = L->back = L->cursor = NULL;
	 L->length = 0;
	 L->index = -1;
	 return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL)
{
    if( pL != NULL && *pL != NULL ){
        while( !isEmpty(*pL) ){ deleteFront(*pL); }
        myFree(*pL);
        *pL = NULL;
    }
}

// newNode()
// Returns reference to new Node object. Initializes next, previous and data fields.
// Private.
Node newNode(int data){
   Node N = myMalloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->previous = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
    if( pN != NULL && *pN != NULL){
        myFree(*pN);
        *pN = NULL;
    }
}

// Access functions -----------------------------------------------------------
int length(List L)
{
	if(L==NULL)
	{
            printf("List Error: calling length() on NULL List reference\n");
            exit(1);
	}
	return L->length;
}
int getIndex(List L)
{
	if(L==NULL)
	{
        printf("List Error: calling getIndex() on NULL List reference\n");
            exit(1);
	}
	return L->index;
}
int front(List L)
{
	if(L==NULL)
	{
            printf("List Error: calling front() on NULL List reference\n");
            exit(1);
	}
	return L->front->data;
}
int back(List L)
{
	if(L==NULL)
	{
            printf("List Error: calling back() on NULL List reference\n");
            exit(1);
	}
	return L->back->data;
}
int getElement(List L)
{
	if(L==NULL)
	{
            printf("List Error: calling getElement() on NULL List reference\n");
            exit(1);
	}
	if(L->cursor==NULL){
            printf("List Error: calling getElement() on NULL cursor reference\n");
            exit(1);
	}
	return L->cursor->data;
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B)
{
	int flag = 1;
	Node N = NULL;
	Node M = NULL;

	if( A==NULL || B==NULL )
    {
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
	}
	N = A->front;
	M = B->front;
	if( A->length != B->length ) { return 0; }
	while( flag && N!=NULL){
		flag = (N->data==M->data);
		N = N->next;
	    M = M->next;
	}
	return flag;
}

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling isEmpty() on NULL List reference\n");
		exit(1);
	}
	return(length(L)<=0);
}

// Manipulation procedures ----------------------------------------------------

// Re-sets List L to the empty state.
void clear(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
	}
	if(!isEmpty(L)){
        int k = length(L);
        for(int i = 0; i < k; i++){
            deleteFront(L);
        }
    }
}

// If 0<=i<=length()-1, moves the cursor to the element
// at index i, otherwise the cursor becomes undefined.
void moveTo(List L, int i)
{
    int j;
    if (L == NULL) {
        printf("List Error: calling moveTo() on NULL List reference\n");
        exit(1);
    }
    if (i >= 0 && i <= length(L) - 1) {
        L->cursor = L->front;
        L->index = i;

        for (j = 0; j < getIndex(L); j++) {
            L->cursor = L->cursor->next;
        }
    }
    else {
        L->index = -1;
        L->cursor = NULL;
    }
}

// If 0<getIndex()<=length()-1, moves the cursor one step toward the
// front of the list. If getIndex()==0, cursor becomes undefined.
// If getIndex()==-1, cursor remains undefined. This operation is
// equivalent to moveTo(getIndex()-1).
void movePrev(List L)
{
	if ( L==NULL )
	{
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(1);
	}
	if ( getIndex(L) > 0 && getIndex(L)<= length(L)-1 )
	{
		L->cursor = L->cursor->previous;
		L->index--;
	}
	else { L->cursor = NULL; L->index = -1; }
}

// If 0<=getIndex()<length()-1, moves the cursor one step toward the
// back of the list. If getIndex()==length()-1, cursor becomes
// undefined. If index==-1, cursor remains undefined. This
// operation is equivalent to moveTo(getIndex()+1).
void moveNext(List L)
{
    if ( L==NULL )
    {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }
    if ( getIndex(L) >= 0 && getIndex(L) < length(L) -1 )
    {
        L->cursor = L->cursor->next;
        L->index++;
    }
    else { L->cursor = NULL; L->index = -1; }
}
void prepend(List L, int data)
{
    if ( L==NULL )
    {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }
    Node node;
    node = newNode(data);
    if ( length(L) == 0 )
    {
        L->front = L->back = node;
    }
    else
    {
        node->next = L->front;
        L->front->previous = node;
        L->front = node;
    }
    L->length++;
    if ( getIndex(L) >= 0 )
    {
        L->index++;
    }
}
void append(List L, int data)
{
    if ( L==NULL )
    {
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }
    Node node;
    node = newNode(data);
	if ( length(L) == 0 ){ L->front = L->back = node; }
	else
        {
		node->previous = L->back;
		L->back->next = node;
		L->back = node;
	}
	L->length++;
}
void insertBefore(List L, int data)
{
    if ( L==NULL )
    {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    Node node;
    node = newNode(data);
	if ( length(L) > 0 && getIndex(L) >= 0 )
    {
        if( getIndex(L) == 0 ){ prepend(L,data); myFree(node); }
        else
        {
            node->next = L->cursor;
            node->previous = L->cursor->previous;
            L->cursor->previous->next = node;
            L->cursor->previous = node;
            L->length++;
            L->index++;
        }
	}
    else
    {
        printf("Cursor Error: insertBefore() called while cursor is undefined");
        exit(1);
    }
}
void insertAfter(List L, int data)
{
    if ( L==NULL )
    {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    Node node;
    node = newNode(data);
	if ( length(L) > 0 && getIndex(L) >= 0 )
    {
	if( getIndex(L) == length(L)-1 )
    {
        append(L,data);
        myFree(node);
	}
    else
    {
            node->previous = L->cursor;
            node->next = L->cursor->next;
            L->cursor->next->previous = node;
            L->cursor->next = node;
            L->length++;
	}
    }
    else
    {
        printf("Cursor Error: insertAfter() called while cursor is undefined");
        exit(1);
    }
}
void deleteFront(List L)
{
    Node N = NULL;

    if ( L==NULL )
    {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if (length(L) <= 0)
    {
        printf(
        "List Error: deleteFront() called on empty list");
        exit(1);
    }

    N = L->front;
    if (length(L) > 1)
    {
        L->front = L->front->next;
        L->length--;
    }
    else
    {
        L->back = L->front = NULL;
        L->length--;
    }
    if (getIndex(L) >= 0)
    {
        L->index--;
    }
    freeNode(&N);
}
void deleteBack(List L)
{
    Node N = NULL;
    N = L->back;
    if ( L==NULL )
    {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if ( getIndex(L) == length(L)-1 )
    {
        L->cursor = NULL;
        L->index = -1;
    }
    if( length(L) <= 0 )
    {
        printf("List Error: deleteBack() called on empty list");
        exit(1);
    }
    if ( length(L) > 1 )
    {
        L->back = L->back->previous;
        L->length--;
    }
    else { L->front = L->back =  NULL; }
    freeNode(&N);
}
void delete(List L)
{
    Node N = NULL;
    N = L->cursor;
    if (length(L) <= 0)
    {
        printf("List Error: delete() called on empty list");
        exit(1);
    }
    if (getIndex(L) < 0)
    {
        printf("List Error: delete() called while cursor is undefined");
        exit(1);
    }
    if (length(L) > 1)
    {
        L->cursor->previous->next = L->cursor->next;
        L->cursor->next->previous = L->cursor->previous;
        L->cursor = NULL;
        L->index = -1;
        L->length--;
    }
    else
    {
        L->front = L->back = NULL;
    }
    freeNode(&N);
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L)
{
    if(L==NULL)
    {
        printf("List Error: calling printList on null list reference\n");
        exit(1);
    }
    for( moveTo(L,0); getIndex(L)>=0; moveNext(L))
    {
        fprintf(out, "%d", getElement(L));
        if(getIndex(L)<=length(L)-1){ fprintf(out, " "); }
    }
}
List copyList(List L)
{
	List K = newList();
    Node N;
    N = L->front;

    while (N != NULL) {
        append(K, N->data);
        N = N->next;
    }

    return K;
}

