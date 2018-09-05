#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"
#define INF -2
#define NIL -1
#include <stdio.h>
#include <stdlib.h>

typedef struct GraphObj * Graph;

Graph newGraph(int num);

void freeGraph(Graph *;

int getOrder(Graph G);

int getSize(Graph G);
	
int getSource(Graph G);

int getParent(Graph G, int v);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void printGraph(FILE * out, Graph G);

Graph copyGraph(Graph G);

Graph transpose(Graph G);

void DFS(Graph G, List s);

#endif
