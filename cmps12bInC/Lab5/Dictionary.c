/* Dictionary.c
 * Created by Ian Feekes December 12th 2017
 * Creates a data structure Dictionary with all its methods
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

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

typedef struct DictionaryObj
{
	Node first;
	Node last; 
	int length; 
}DictionaryObj;

typedef DictionaryObj* Dictionary; 

Dictionary newDictionary()
{
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert(D!=NULL);
	D->first=NULL;
	D->last=NULL;
	D->length=0;
	return(D);
}

void freeDictionary(Dictionary* pD)
{
	if(pD!=NULL && *pD!=NULL)
	{
		//makeEmpty(*pD);
		free(*pD);
		*pD=NULL;
	}
}

int isEmpty(Dictionary D)
{
	return(D->length==0);
}

int size(Dictionary D)
{
	return D->length;
}

char* lookup(Dictionary D, char* k)
{
    if(isEmpty(D))return NULL;
	Node N;
	N=D->first;
    
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

void insert(Dictionary D, char* k, char* v)
{
	if(lookup(D, k)!=NULL)
	{
		printf("Error, key already exists \n");
		return;
	}
	if(!isEmpty(D))
	{
        Node N = D->first;
		while(N->next!=NULL)
		{
			N=N->next; 
		}
		Node temp = newNode(k, v);
		N->next=temp;
	}
	else
	{
		Node temp = newNode(k, v);
		D->first=temp; 
	}
	D->length++; 
}

void delete(Dictionary D, char* k)
{
	if(lookup(D, k)==NULL)
	{
		printf("Error, delete() called on an empty key");
		return;
	}
	D->length--; 
	if(isEmpty(D))
	{
        printf("Error, delete() called on an empty dictionary");
        return;
	}
	else if(size(D)==1)
	{
		makeEmpty(D);
	}
    else if(!strcmp(D->first->key, k)) /* if we are deleting the first element */
    {
        Node N = D->first;
        Node temp = N->next;
        freeNode(&N);
        D->first=temp;
    }
	else
	{
        //Node temp = N;
		Node N = D->first;
        Node temp = N;
		while(strcmp(N->key, k))
		{
            temp = N;
			N=N->next;
		}
        
        temp->next=N->next;
        freeNode(&N);
        
		/*Node temp=N->next;
		N->next=temp->next;
		freeNode(&temp);*/
	}
}

void makeEmpty(Dictionary D)
{
	Node N = D->first;
	Node temp = N;
	while(N->next!=NULL)
	{
		N=N->next;
		freeNode(&temp);
		temp=N;
	}
	D->length=0;		
	D->first=NULL;
	D->last=NULL; 
}

void printDictionary(FILE* out, Dictionary D)
{
    Node N;
    for(N=D->first;N->next!=NULL;N=N->next)
    {
        fprintf(out, "key = %s, value = %s, ", N->key, N->value);
    }
    fprintf(out, "\n");
}

