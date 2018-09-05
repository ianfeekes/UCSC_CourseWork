//Ian Feekes
//#1474914
//ifeekes@ucsc.edu
//pa4
//graphTest.c

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[])
{
 Graph G = newGraph(50);
 for(int i = 1; i < getOrder(G); i++) addEdge(G, i, i + 1);
 printGraph(stdout, G);
 BFS(G, 1);
 fprintf(stdout,"The graph's total distance is %d", getDist(G, 50));
 addEdge(G, 9, 31);
 printGraph(stdout, G);
 append(G, 1);
 printGraph(stdout, G);
 moveFront(G);
 moveNext(G);
 printGraph(stdout, G);
 freeGraph(&G);
 exit(1);
}



