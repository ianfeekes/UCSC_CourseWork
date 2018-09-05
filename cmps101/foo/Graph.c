#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include <assert.h>
#include <errno.h>
#define NIL 0



typedef struct GraphObj {
	List *adj; 
	int* color; 
	int* d; 
	int* f; 
	int* P; 
	int order; 
	int size; 
	int cc; 
} GraphObj;

typedef struct GraphObj* Graph;

Graph newGraph(int n) 
{
	Graph G = malloc(sizeof(Graph));

	G->adj = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(int));
	G->d = calloc(n+1, sizeof(int));
	G->f = calloc(n+1, sizeof(int));
	G->P = calloc(n+1, sizeof(int));
	G->order = n;
	G->size = 0;
	G->cc = 0;

	int i;
	for ( i = 1; i <= n; ++i ) {
		G->adj[i] = newList();
		G->color[i] = WHITE;
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;
		G->P[i] = NIL;
	}
	return (G);
}

void freeGraph(Graph* pG) {
	/*if( pG == NULL || (*pG) == NULL ) return;
	int i;
	for ( i = 1; i <= getOrder(*pG); ++i ) {
		freeList(&((*pG)->adj[i]));
	}
	free((*pG)->adj);
	free((*pG)->color);
	free((*pG)->d);
	free((*pG)->f);
	free((*pG)->P);
	free(*pG);
	*pG = NULL;*/
 if((*pG)!=NULL)
 {
  free((*pG)->d);
  free((*pG)->f);
  free((*pG)->P);
  free((*pG)->color);
  for(int i=1; i<=getOrder(*pG); ++i) freeList(&((*pG)->adj[i]));
  free((*pG)->adj);
  free(*pG);
  *pG=NULL;
 }
}



int getOrder(Graph G) 
{
 if( G == NULL ) 
 {
  printf("Error: getOrder() called on NULL Graph\n");
  exit(1);
 }
 return (G->order);
}

int getSize(Graph G) 
{
 if( G == NULL )
 {
  printf("Error: getSize() called on NULL Graph\n");
  exit(1);
 }
 return (G->size);
}

int getCC(Graph G) 
{
 if( G == NULL ) 
 {
  printf("Error: getCC() called on NULL Graph\n");
  exit(1);
 }
 return (G->cc);
}

int getColor(Graph G, int u) 
{
 if (( G == NULL )||( u < 1 || u > getOrder(G) )) 
 {
  printf("Error: getColor() called on NULL Graph\n");
  exit(1);
 }
 return (G->color[u]);
}

int getParent(Graph G, int u) 
{
 if( G == NULL )
 {
  printf("Error: getParent()called on NULL Graph\n");
  exit(1);
 }
 if( u < 1 || u > getOrder(G) )
 {
  printf("Graph Error: calling getParent() on out of index array P\n");
  exit(1);
 }
 return (G->P[u]);
}

int getDiscover(Graph G, int u)
{
 if (( G == NULL )||( u < 1 || u > getOrder(G) )) 
 {
  printf("Graph Error: calling getDiscover() on NULL GraphRef\n");
  exit(1);
 }
 return (G->d[u]);
}

int getFinish(Graph G, int u) {
	if ( G == NULL ) {
		printf("Graph Error: calling getFinish() on NULL GraphRef\n");
		exit(1);
	}
	if ( u < 1 || u > getOrder(G) ) {
		printf("Graph Error: calling getFinish() on out of index array d\n");
		exit(1);
	}

	return (G->f[u]);
}


void makeNull(Graph G) {
	if ( G == NULL ) {
		printf("Graph Error: calling makeNull() on NULL GraphRef\n");
		exit(1);
	}

	int i;
	for ( i = 1; i <= getOrder(G); ++i ) {
		makeEmpty(G->adj[i]); 
		G->color[i] = NIL;
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;
		G->P[i] = NIL;
	}
	G->size = 0;
	G->cc = 0;
}

void addArc(Graph G, int u, int v) {
	if ( G == NULL ) {
		printf("Graph Error: calling addArc() on NULL GraphRef\n");
		exit(1);
	}
	if ( u < 1 || u > getOrder(G) ) {
		printf("Graph Error: calling addArc() on u non-existent within bounds of order\n");
		exit(1);
	}
	if ( v < 1 || v > getOrder(G) ) {
		printf("Graph Error: calling addArc() on v non-existent within bounds of order\n");
		exit(1);
	}

	insertAfterBack(G->adj[u], v);
	++(G->size);
}


void Visit(Graph G, List L, int x, int* time){
	G->color[x] = GRAY;
	G->d[x] = (++(*time));
	if ( !isEmpty(G->adj[x]) ) { moveFront(G->adj[x]); }
	int y;
	while ( !offEnd(G->adj[x]) ) {
		y = getCurrent(G->adj[x]);
		if ( G->color[y] == WHITE ) {
			G->P[y] = x;
			Visit(G, L, y, &(*time));
		}
		moveNext(G->adj[x]);

	}
	G->color[x] = BLACK;
	G->f[x] = (++(*time));
	insertBeforeFront(L, x);
}

void DFS(Graph G, List S) {
	if ( G == NULL ) {
		printf("Graph Error: calling DFS() on NULL GraphRef\n");
		exit(1);
	}
	if ( getOrder(G) != getLength(S) ) {
		printf("Graph Error: calling DFS() on unequal sized order and length\n");
		exit(1);
	}

	int i, x, time;
	List L = newList();
	for ( i = 1; i <= getOrder(G); ++i) {
		G->color[i] = WHITE;
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;
		G->P[i] = NIL;
	}
	time = 0;
	G->cc = 0;
	if ( !isEmpty(S) ) { moveFront(S); }
	while ( !offEnd(S) ) {
		x = getCurrent(S);
		if ( G->color[x] == WHITE ) {
			Visit(G, L, x, &time);
			++(G->cc);
		}
		moveNext(S);
	}

	makeEmpty(S);
	if ( !isEmpty(L) ) { moveFront(L); }
	while ( !offEnd(L) ) {
		insertAfterBack(S, getCurrent(L));
		moveNext(L);
	}
	freeList(&L);
}


Graph transpose(Graph G) {
	if ( G == NULL ) {
		printf("Graph Error: calling transpose() on NULL GraphRef\n");
		exit(1);
	}

	Graph T = newGraph(getOrder(G));
	int i, x;
	for ( i = 1; i <= getOrder(G); ++i) {
		if ( !isEmpty(G->adj[i]) ) { moveFront(G->adj[i]); }
		while ( !offEnd(G->adj[i]) ) {
			x = getCurrent(G->adj[i]);
			addArc(T, x, i);
			moveNext(G->adj[i]);
		}
	}
	return (T);
}

Graph copyGraph(Graph G) {
	if ( G == NULL ) {
		printf("Graph Error: calling copyGraph() on NULL GraphRef\n");
		exit(1);
	}

	Graph N = newGraph(getOrder(G));
	int i;
	for ( i = 1; i <= getOrder(N); ++i ) {
		if ( !isEmpty(G->adj[i]) ) { moveFront(G->adj[i]); }
		while ( !offEnd(G->adj[i]) ) {
			insertAfterBack(N->adj[i], getCurrent(G->adj[i]));
			moveNext(G->adj[i]);
		}
		N->color[i] = getColor(G, i);
		N->d[i] = getDiscover(G, i);
		N->f[i] = getFinish(G, i);
		N->P[i] = getParent(G, i);
	}
	N->size = getSize(G);
	N->cc = getCC(G);
	return (N);
}

void printGraph(FILE* out, Graph G){
	if ( G == NULL ) {
		printf("Graph Error: calling printGraph() on NULL GraphRef\n");
		exit(1);
	}

	fprintf(out, "Adjacency list representation of G:\n");
	int i, temp;
	for ( i = 1; i <= getOrder(G); ++i ) {
		fprintf(out, "%d:", i);
		if ( !isEmpty(G->adj[i]) ) {
			moveFront(G->adj[i]);
			while ( !offEnd(G->adj[i]) ) {
				temp = getCurrent(G->adj[i]);
				moveNext(G->adj[i]);
				fprintf(out, " %d", temp);
			}
		}
		fprintf(out, "\n");
	}
}
