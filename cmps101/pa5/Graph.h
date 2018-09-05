//Ian Feekes
//#1474914
//ifeekes@ucsc.edu
//pa5
//Graph.h

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"


typedef struct GraphObj* Graph;

Graph newGraph(int n);

void freeGraph(Graph* pG);

int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

void addArc(Graph G, int u, int v);

void addEdge(Graph G, int u, int v);

void DFS(Graph G, List S);

Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);

int getSource(Graph G);

int Visit(int x, Graph G, List S, int time);
#endif 

