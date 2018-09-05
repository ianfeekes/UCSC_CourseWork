//Ian Feekes
//#1474914
//ifeekes@ucsc.edu
//pa4
//List.c

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "List.h"
#include <assert.h>
#include <string.h>

Node newNode(int data)
{
 Node N = (Node) malloc(sizeof(struct ListNode));
 N->data = data;
 N->next = NULL;
 N->previous = NULL;
 return(N);
}

List newList(void)
{
 List L = malloc(sizeof(struct ListObject));
 assert(L != NULL);				//when we create a new list it must be NULL
 L->front = NULL;
 L->back = NULL;
 L->cursor = NULL;
 L->length = 0;
 L->index = -1;
 return(L);
}

void freeList(List* pL)
{
 List temp = *pL;
 assert(temp != NULL);  
 if (length(temp) != 0) clear(temp);
 free(*pL);
 *pL = NULL;
}

void freeNode(Node* pN)
{
 free(*pN);
 *pN = NULL;
}

int length(List L)
{
 if(L != NULL) return L->length;
 else
 {
  printf("Error: call to length() returns NULL");
  exit(1);
 }
}

int getIndex(List L)
{
 if(L != NULL)return L->index;
 else
 {
  printf("Error: cannot get the index of a null list");
  exit(1);
 }
}

int front(List L)
{
 if(L != NULL)
 {
  if(length(L) > 0) return(L->front->data);
  else return(-1); 
 }
 else
 {
  printf("Error: cannot get the front a null list");
  exit(1);
 }
}

int back(List L)
{
 if(L != NULL)
 {
  if (length(L) > 0)return(L->back->data);
  else return (-1);
 }
 else
 {
  printf("Error: cannot get the back of a null list");
  exit(1);
 }
}

int getElement(List L)
{
 if(L != NULL)
 {
  if (length(L) > 0 && getIndex(L) >= 0)return(L->cursor->data);
  else return(-1);
 }
 else
 {
  printf("Error: cannot get cursor of a null list");
  exit(1);
 }
}

int equals(List A, List B)
{
 if(A != NULL && B != NULL)
 {
  if(length(A) != length(B))return(0);
  else
  {
   Node tempA = A->front;
   Node tempB = B->front;
   for (; tempA != NULL; tempA = tempA->next)
   {
    if (tempA->data != tempB->data)return(0);
    tempB = tempB->next;
   }
  }
  return(1);
 }
 else
 {
  printf("Error: one of the lists in comparison is null");
  exit(1);
 }
}

void clear(List L)
{
 if(L != NULL)
 {
  for (L->cursor = L->front; L->cursor != NULL;)
  {
   Node temp = L->cursor;
   L->cursor = L->cursor->next;
   free(temp);
  }
  L->front = L->back = L->cursor = NULL;
  L->index = -1;
  L->length = 0;
  }
  else
  {
  printf("Error: list is null");
  exit(1); 
  }
}

void moveTo(List L, int i)
{
 if(L != NULL)
 {
  if (length(L) != 0)
  {
   if (i >= 0 && i <= length(L) -1)
   {
    L->cursor = L->front;
    L->index = 0;
    if (i == 0) return;
    for (; getIndex(L) < i; moveNext(L)){}		//do nothing
   }
  }
 }
 else
 {
  printf("Error: cannot move through an empty list");
  exit(1);
 }
}

void movePrev(List L)
{
 if(L != NULL)
 {
  if (getIndex(L) == 0)
  {
   L->cursor = NULL;
   L->index = -1;
  }
  else if (0 < getIndex(L) && getIndex(L) <= length(L) - 1)
  {
   L->cursor = L->cursor->previous;
   L->index--;
  }
 }
 else
 {
  printf("Error: one of you're lists is improperly declared - movePrev()");
  exit(1);
 }
}

void moveNext(List L)
{
 if(L != NULL)
 {
  if (getIndex(L) == length(L) - 1)
  {
   L->cursor = NULL;
   L->index = -1;
  }
  else if (0 <= getIndex(L) && getIndex(L) < length(L) -1)
  {
   L->cursor = L->cursor->next;
   L->index++;
  }
 }
 else
 {
  printf("Error: one of you're lists is improperly declared - moveNext()");
  exit(1);
 }
}

void prepend(List L, int data)
{
 if(L != NULL)
 {
  if (length(L) == 0)
  {
   Node N = newNode(data);
   L->front = N;
   L->back = N;
   L->length++;
  }
  else if (length(L) > 0)
  {
   Node N = newNode(data);
   N->next = L->front;
   L->front->previous = N;
   L->front = N;
   L->length++;
   if(getIndex(L) != -1)L->index++;
  }
 }
 else
 {
  printf("Error: list is NULl for prepend()");
  exit(1);
 }
}

void append(List L, int data)
{
 if(L != NULL)
 {
  if (length(L) == 0)
  {
   Node N = newNode(data);
   L->front = N;
   L->back = N;
   L->length++;
  }
  else if (length(L) > 0)
  {
   Node N = newNode(data);
   N->previous = L->back;
   L->back->next = N;
   L->back = N;
   L->length++;
  }
 }
 else
 {
  printf("Error: list is NULL for append()");
  exit(1);
 }
}

void insertBefore(List L, int data)
{
 if(L != NULL)
 {
  if(length(L) > 0 && getIndex(L) >= 0)
  {
   Node N = newNode(data);
   Node temp = L->cursor->previous;
   temp->next = N;
   N->previous = N;
   N->next = L->cursor;
   L->cursor->previous = N;
   L->length++;
   L->index++;
  }
 }
 else
 {
  printf("Error: insertBefore called on a null list");
  exit(1);
 }
}

void insertAfter(List L, int data)
{
 if(L != NULL)
 {
  if(length(L) > 0 && getIndex(L) >= 0)
  {
   Node N = newNode(data);
   Node temp = L->cursor->next;
   temp->previous = N;
   N->next = temp;
   N->previous = L->cursor;
   L->cursor->next = N;
   L->length++;
  }	
 }
 else
 {
  printf("Error: insertAfter called on a null list");
  exit(1);
 }
}

void deleteFront(List L)
{
 if(L != NULL)
 {
  if (length(L) >= 2)
  {
   Node temp = L->front->next;
   L->front->next->previous = NULL;
   L->front->next = NULL;
   freeNode(&(L->front));
   L->front = temp;
   L->length--;
   if(getIndex(L) == 0)L->index = -1;
   else if(getIndex(L) != -1) L->index--;
   else if (length(L) == 1)
   {
    Node temp = L->front;
    L->front = NULL;
    L->back = NULL;
    free(temp);
    L->length = 0;
    if(getIndex(L) == 0) L->index = -1;
   }
  }
  else
  {
   printf("Error: deleteFront called on a null list");
   exit(1);
  }
 }
}

void deleteBack(List L)
{
 if(L != NULL)
 {
  if (length(L) >=  2)
  {
   Node temp = L->back->previous; 
   L->back->previous = NULL;
   temp->next = NULL;
   L->back = NULL;
   free(L->back);
   L->back = temp;
   L->length--;
   if(getIndex(L) == length(L) - 1)L->index = -1;
  }
  else if(length(L) == 1)
  {
   Node temp = L->front;
   L->front = NULL;
   L->back = NULL;
   free(temp);
   L->length = 0;
   if(getIndex(L) == 0) L->index = -1;
  }
 }
 else
 {
  printf("Error: deleteBack called on a null list");
  exit(1);
 }
}

void delete(List L)
{
 if(L != NULL)
 {
  if (length(L) > 0 && getIndex(L) >= 0)
  {
   Node temp = L->cursor;
   Node left = L->cursor->previous;
   Node right = L->cursor->next;
   left->next = right;
   right->previous = left;
   L->cursor->next = NULL;
   L->cursor->previous = NULL;
   L->cursor = NULL;
   free(temp);
   L->index = -1;
   L->length--;
  }
 }
 else
 {
  printf("Error: delete called on an empty list");
  exit(1);
 }
}

void printList(FILE* out, List L)
{
 L->cursor = L->front;
 while (L->cursor != NULL)
 {
  fprintf(out,"%i ", (int) (L->cursor->data));
  L->cursor = L->cursor->next;
 }
}

List copyList(List L)
{
 List newL = newList();
 for (Node temp = L->front; temp != NULL; temp = temp->next) append(newL, temp->data);
 return(newL);
}
