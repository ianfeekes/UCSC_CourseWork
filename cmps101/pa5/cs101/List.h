//Ian Feekes
//#1474914
//ifeekes@ucsc.edu
//List.h

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObject *List;

typedef struct ListNode *Node;

struct ListNode
{
 int data;
 Node previous;
 Node next;
};

struct ListObject
{
 Node front;
 Node back;
 Node cursor;
 int length;
 int index;
};

Node newNode(int);
 
List newList(void);

void freeList(List *pL);

int length(List);

int getIndex(List);

int front(List);

int back(List);

int getElement(List);

int equals(List, List);

void clear(List);

void moveTo(List, int);

void movePrev(List);

void moveNext(List);

void prepend(List, int);

void append(List, int);

void insertBefore(List, int);

void insertAfter(List, int);

void deleteFront(List);

void deleteBack(List);

void delete(List);

void printList(FILE*, List);

List copyList(List);

#endif

