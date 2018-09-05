/* Ian Feekes
 *#1474914
 *ifeekes@ucsc.edu
 *List.h
 *PA2
 *Tantalo
 */

 #ifndef _LIST_H_INCLUDE_
 #define _List_H_INCLUDE_

 typedef struct ListObj* List;

 //defines all the functions for use by List.c
 
 //makes a new empty list and returns a pointer to it
 List newList(void);

 //Frees all the memory of the list with Queue *pQ going NULL
 void freeList(List*pL);

 //returns length
 int length(List L);

 //returns cursor index. If cursor is undefined return -1
 int index(List L);

 //returns front element. Throws exception/error message if !length()>0
 int front(List L);
 
 //returns back element with an exception of same precondition as front()
 int back(List L);
 
 //returns the cursor element if length()>0 && index()>=0
 int get(List L);

 // if A and B are the same sequence returns TRUE
 int equals(List A, List B);


void clear(List L);
 //places the cursor under the front element. If list it empty do nothing
 void freeList(List* pL);
 //same as front but under the back element
 void moveBack(List L);

 /*cursor is defined and not at front, move it one node closer to the front.
 *If cursor is defined and at the front, cursor becomes undefined
 *If cursor is undefined do nothing
 */
 void movePrev(List L);

 //same thing as previous cept it moves the cursor towards the back, not the front
 void moveNext(List L);

 //New element gets put into the list. If length()>0 put it before the first element 
 //(the new element is the new first)
 void prepend(List L, int data);
 
 //Same as prepend just put the new element to the back of the list
 void append(List L, int data);

 //inserts a new element before the cursor if length()>0 && index()>=0
 void insertBefore(List L, int data);
 
 //inserts a new element after the cursor with same preconditions as above
 void insertAfter(List L, int data);

 //deletes the front element if length()>0 else throws error
 void deleteFront(List L);

 //same as delete front just deletes the back element w/same preconditions
 void deleteBack(List L);

 //deletes the cursor element, setting the cursor=NULL
 //length()>0 && index()>=0
 void delete(List L);

 //prints the given list like toString in the output file
 void printList(FILE* out, List L);
 
 //makes an exact copy of the sequence and data of the list, just with no cursor 
 List copyList(List L);

 #endif
