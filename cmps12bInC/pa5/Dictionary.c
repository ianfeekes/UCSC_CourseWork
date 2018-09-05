/* Dictionary.c
 * Ian Feekes created December 12th 2017
 * Used to implement hashing in C
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"

const int tableSize = 101;

/* The functions below are to be added to Dictionary.c
 *------------------------------------------------------------------------------------------------
 */


// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift)
{
    int sizeInBits = 8*sizeof(unsigned int); shift = shift & (sizeInBits - 1);
    if ( shift == 0 ) return value;
    return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input)
{
    unsigned int result = 0xBAE86554;
    while (*input)
    {
        result ^= *input++;
        result = rotate_left(result, 5);
    }
    return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key)
{
    return pre_hash(key)%tableSize;
}

typedef struct NodeObj
{
    char* key;
    char* value;
    struct NodeObj* next;
}NodeObj;


typedef NodeObj* Node;

Node newNode(char* k, char* v)
{
    Node N = malloc(sizeof(NodeObj));
    assert(N!=NULL);
    N->key = calloc(strlen(k)+1, sizeof(char));
    N->value = calloc(strlen(v)+1, sizeof(char));
    strcpy(N->key, k);
    strcpy(N->value, v);
    N->next=NULL;
    return(N);
}

void freeNode(Node* pN)
{
    if(pN!=NULL && *pN!=NULL)
    {
        free((*pN)->key);
        free((*pN)->value);
        free(*pN);
        *pN=NULL;
    }
}

typedef struct ListObj
{
    Node first;
    Node last;
    int length;
}ListObj;

typedef ListObj* List;

List newList()
{
    List L = malloc(sizeof(ListObj));
    assert(L!=NULL);
    L->first=NULL;
    L->last=NULL;
    L->length=0;
    return(L);
}

void freeList(List* pL)
{
    if(pL!=NULL && *pL!=NULL)
    {
        //makeEmpty(*pD);
        free(*pL);
        *pL=NULL;
    }
}

int isEmptyList(List L)
{
    return(L->length==0);
}

int sizeList(List L)
{
    return L->length;
}

char* lookupList(List L, char* k)
{
    if(isEmptyList(L))return NULL;
    Node N;
    N=L->first;
    
    while(N!=NULL)
    {
        if(!strcmp(N->key, k))
        {
            return N->value;
        }
        N = N->next;
    }
    return NULL;
}

void insertList(List L, char* k, char* v)
{
    if(lookupList(L, k)!=NULL)
    {
        printf("Error, key already exists \n");
        return;
    }
    if(!isEmptyList(L))
    {
        Node N = L->first;
        while(N!=NULL)
        {
            N=N->next;
        }
        Node temp = newNode(k, v);
        N=temp;
    }
    else
    {
        Node temp = newNode(k, v);
        L->first=temp;
    }
    L->length++;
}

void deleteList(List L, char* k)
{
    if(lookupList(L, k)==NULL)
    {
        printf("Error: delete() called on an empty key");
        return;
    }
    if(isEmptyList(L))
    {
        printf("Error: delete() called on an empty list \n");
        return;
    }
    else if(sizeList(L)==1)
    {
        L->first=0;
        L->length--;
    }
    else if(!strcmp(L->first->key, k)) /* if we are deleting the first element */
    {
        Node N = L->first;
        Node temp = N->next;
        freeNode(&N);
        L->first=temp;
        L->length--;
    }
    else
    {
        //Node temp = N;
        Node N = L->first;
        Node temp = N;
        while(strcmp(N->key, k))
        {
            temp = N;
            N=N->next;
        }
        
        temp->next=N->next;
        freeNode(&N);
        L->length--;
        /*Node temp=N->next;
         N->next=temp->next;
         freeNode(&temp);*/
    }
}

void makeEmptyList(List L)
{
    Node N = L->first;
    Node temp = N;
    /*change the while loop to make it so that it's while N!=NULL - that might fix the segmentation fault*/
    while(N!=NULL) /*Lets see if this works*/ 
    {
        N=N->next;
        freeNode(&temp);
        temp=N;
    }
    L->length=0;
    L->first=NULL;
    L->last=NULL;
}

void printList(FILE* out, Node N)
{
    while(N!=NULL)
    {
        fprintf(out, "key = %s, value = %s, ", N->key, N->value);
        N=N->next;
    }
    fprintf(out, "\n");
}

void freeListArray(List** pL){
    
    if( pL != NULL && *pL != NULL ){
        free(*pL);
        *pL = NULL;
    }
}

typedef struct DictionaryObj
{
    int length;
    List* L;
}DictionaryObj;

typedef DictionaryObj* Dictionary;

Dictionary newDictionary()
{
    Dictionary D = malloc(sizeof(DictionaryObj));
    assert(D!=NULL);
    D->L = calloc(tableSize, sizeof(List*));
    for(int i=0;i<tableSize;i++)
    {
        D->L[i]=newList();
    }
    D->length=0;
    return D;
}

void freeDictionary(Dictionary* pD)
{
    makeEmpty(*pD);
    for(int i=0;i<tableSize;i++)
    {
        freeList(&((*pD)->L[i]));
    }
    freeListArray(&((*pD)->L));
    free(*pD);
    *pD=NULL;
}

int isEmpty(Dictionary D)
{
    return D->length==0;
}

int size(Dictionary D)
{
    return D->length;
}

char* lookup(Dictionary D, char* k)
{
    int hashIndex=hash(k);
    return(lookupList(D->L[hashIndex], k));
}

void insert(Dictionary D, char* k, char* v)
{
    if(lookup(D, k)!=NULL)
    {
        printf("Error: insert() called on an already existing key \n");
        return;
    }
    int hashIndex=hash(k);
    insertList(D->L[hashIndex], k, v);
    D->length++;
}

void delete(Dictionary D, char* k)
{
    if(lookup(D, k)==NULL)
    {
        printf("Error: delete() called on a nonexistent key \n");
        return;
    }
    int hashIndex=hash(k);
    deleteList(D->L[hashIndex], k);
    D->length--;
}

void makeEmpty(Dictionary D)
{
    if(D==NULL)
    {
        printf("Error: makeEmpty() called on an already empty list \n");
        return;
    }
    for(int i=0;i<tableSize;i++)
    {
        makeEmptyList(D->L[i]);
    }
    D->length=0;
}

void printDictionary(FILE* out, Dictionary D)
{
    if(D==NULL)
    {
        printf("Error: printDictionary() called on an empty dictionary");
        return;
    }
    for(int i=0; i<tableSize;i++)
    {
        if(D->L[i]->first!=NULL)printList(out, D->L[i]->first);
    }
}

