//Ian Feekes
//#1474914
//ifeekes@ucsc.edu
//PA2
//List.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"
#define TRUE 1
#define FALSE 0

typedef struct NodeObj//defines Node
{
    int data;
    struct NodeObj *next;
    struct NodeObj *prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj//defines List
{
	Node front;
	Node back;
	Node cursor;	
	int length;
} ListObj;

//***Constructors-Destructors---------------------------------------------------------

List newList(void)		//creates a new empty list and returns it
{
	List L;
	L = malloc(sizeof(ListObj));
	assert(L!=NULL);
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	return L;
}

void freeList(List* pL)		//removes pointers of the list and sets it to null, freeing it Node by Node
{
	if(pL != NULL && *pL != NULL)
	{
		while(length(*pL) > 0 )
		{
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

Node newNode(int data)		//creates a new empty node and returns it
{
   	Node N = malloc(sizeof(NodeObj));
   	assert(N!=NULL);
  	N->data = data;
  	N->next = NULL;
   	N->prev = NULL;
   	return(N);
}

// Access functions -----------------------------------------------------------

int length(List L)		//returns length
{
	if(L == NULL)
	{
		printf("Error: cannot call length() on an empty list\n");
 		exit(1);
	}
	return L->length;
}

int index(List L)		//checks for cursor element and returns it by looping through until we hit the end of the list
{
	if(L->cursor == NULL) return -1;	//if there is no cursor then we return -1
    	else
	{
        	Node N = L->front;
        	int i = 0;
        	while(N != NULL)
		{
            		if(N == L->cursor)return i;
            		N = N->next;
           		i++;
         	}
      	}
    	return -1;		//if we haven't found it we return -1 by default
}

int front(List L)
{
	if(length(L) > 0) return L->front->data; //will print error function by default if the length>0
	printf("Error: cannot call front() on an empty list\n");
	exit(1);
}

int back(List L)
{       
        if(length(L) > 0) return L->back->data; //will print error function by default if the length>0
        printf("Error: cannot call back() on an empty list\n");
        exit(1);
}

int get(List L)	//returns cursor element if the length and cursor index match the prerequisites
{
	if((length(L) > 0) && (index(L) >= 0)) return L->cursor->data; 
        printf("Error: cannot call get() with an empty List or with a list without a cursor\n");
        exit(1);
}

int equals(List A, List B)		//loops through looking for an incongruency in either length or in Node data, if it finds none returns true as default
{
	if(A->length != B->length) return FALSE;
      	Node N = A->front;
      	Node O = B->front;
      	for(int i = 0; i<A->length ; i++)
	{
        	if( N->data != O->data) return FALSE;
         	N = N->next;
        	O = O->next;
        }	
      return TRUE;				//returns true by default. Will only return false if the lengths aren't equal or if data in any of the nodes is found incongruent
}

void clear(List L)				//makes all parts of the list emtpy
{
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
}

void moveFront(List L)				//sets cursor to front if list isn't empty
{
	if(length(L) != 0) L->cursor = L->front;
}

void moveBack(List L)				//sets cursor to back if list isn't empty
{
        if(length(L) != 0) L->cursor = L->back;
}

void movePrev(List L)				//moves cursor back one or sets it to null if it is equal to front
{
	if(index(L)!=-1) L->cursor = L->cursor->prev;
}

void moveNext(List L)				//moves cursor forward one or sets it to null if it is equal to back
{
        if(index(L)!=-1) L->cursor = L->cursor->next;
}

void prepend(List L, int data)			//new node at front
{
	Node N = newNode(data);	
	if(length(L) == 0)	
	{
		L->front = N;
		L-> back = N;
	} 
	else
	{
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}
	L->length++;				//increments length because new node
}

void append(List L, int data)//literally same thing as prepend just switch front for back and switch next for prev and it all works
{
        Node N = newNode(data);
        if(length(L) == 0)
        {
                L->front = N;
                L-> back = N;
        } 
        else
        {
                N->prev = L->back;
                L->back->next = N;
                L->back = N;
        }
        L->length++;
}

void insertBefore(List L, int data)
{
	if (L->cursor == L->front) prepend(L, data);	//if we want to insert before the head it's the same thing as prepending so we can skip out of this method in this case
	if(length(L) > 0)
	{
		Node N = newNode(data); 
		N->prev = L->cursor->prev;
        	N->next = L->cursor;
        	N->prev->next = N;
        	L->cursor->prev = N;
 		L->length++;				//making a new node so we must increment. 
    }
}

void insertAfter(List L, int data)
{
        if (L->cursor == L->back) append(L, data);     //if we want to insert before the head it's the same thing as prepending so we can skip out of this method in this case
        if(length(L) > 0)
        {
                Node N = newNode(data);
                N->prev = L->cursor;
                N->next = L->cursor->next;
                N->next->prev = N;
                L->cursor->next = N;
                L->length++;                            //making a new node so we must increment. 
    }
}

void deleteFront(List L)
{
	if(length(L)> 0)				//do nothing if there are no elements in the list
	{
		Node O  = NULL;
		O = L->front;
		if(length(L)> 1)
		{
			L->front = L->front->next;
		}
		 else					//if there is only one element in the list
		{
			L->front = NULL;
			L->back = NULL;
		}
		L->length--;				//decrements the length and kills the node from memory so that we don't have any leakage
	}
}

void deleteBack(List L)					//reverse methods can achieve what you want by copying and pastinng and just replacing front with back and next with prev
{ 
        if(length(L)> 0)                                //do nothing if there are no elements in the list
        {
                Node O  = NULL;
                O = L->back;
                if(length(L)> 1)
                {
                        L->back = L->back->prev;
                } 
                 else                                   //if there is only one element in the list
                {
                        L->front = NULL;
                        L->back = NULL;
                }
                L->length--;                            //decrements the length and kills the node from memory so that we don't have any leakage
        }
}

void delete(List L)					//if the list is empty we don't really have to do anything
{
	if(!length(L)>0 && !index(L)>= 0) return;
	else if(L->cursor == L->front)
	{
		deleteFront(L);
		L->cursor = NULL;
	}
	else if(L->cursor == L->back)
	{
		deleteBack(L);
		L->cursor = NULL;
	}
	else
	{
		Node O = NULL;
		O = L->cursor;
		L->cursor->prev->next = L->cursor->next;
         	L->cursor->next->prev = L->cursor->prev;
            	L->length--;
	}
}

void printList(FILE* out, List L)
{
	Node N = NULL;
   	if( L== NULL)
	{
      		fprintf(out, "Error. Cannot print out a NULL List\n");
      		exit(1);
   	}
	for(N = L->front; N != NULL; N = N->next)
	{
		fprintf(out, "%d ", N->data);
   	}
}

List copyList(List L)	//copies the new list by going through all the Nodes in the argument list and periodically appending them to the new copied list. This allows us to ignore cursors and the like. 
{
	List A = newList();
	Node N = NULL;
	for(N = L->front; N != NULL; N = N->next)
	{
		append(A, N->data);
	}
	return A;
}

