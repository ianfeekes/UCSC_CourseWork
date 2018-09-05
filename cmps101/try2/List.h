#include <stdio.h>
#include <stdlib.h>
#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List;

typedef struct ListNode *Node;

struct ListNode{
	int data;
	Node previous;
	Node next;
}ListNode;

struct ListObject{
    Node front;
	Node back;
	Node cursor;
	int length;
	int index;
}ListObject;

Node newNode(int);

List newList(void);

void freeList(List* pL);

int length(List L);

int getIndex(List L);

int front(List L);

int back(List L);

int getElement(List L);

int equals(List A, List B);

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

void sortList(List L);

void printList(FILE* out, List L);

List copyList(List L);

void insertSorted(List L, int n);

#endif
