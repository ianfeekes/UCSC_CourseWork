//Ian Feekes
//ifeekes@ucsc.edu
//#1474914
//pa5
//GraphTest.c

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[])
{
 int i;
 int n = 8;
 List S = newList();
 Graph J = newGraph(n);
 for(i=1; i<=n; i++) append(S, i);
 addArc(J, 1,2);
 addArc(J, 1,5);
 addArc(J, 2,5);
 addArc(J, 2,6);
 addArc(J, 3,2);
 addArc(J, 3,4);
 addArc(J, 3,6);
 addArc(J, 3,7);
 addArc(J, 3,8);
 addArc(J, 6,5);
 addArc(J, 6,7);
 addArc(J, 8,4);
 addArc(J, 8,7);
 printGraph(stdout, J);
 DFS(J, S);
 fprintf(stdout, "\n");
 fprintf(stdout, "x:  d  f  p\n");
 for(i=1; i<=n; i++)
 {
  fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(J, i), getFinish(J, i), getParent(J, i));
 }
 fprintf(stdout, "\n");
 printList(stdout, S);
 fprintf(stdout, "\n");
 freeGraph(&J);
 freeList(&S);
 n=3;
 Graph G = newGraph(n);			//makes new graph G
 addArc(G, 1, 2);
 addArc(G, 1, 3);
 addArc(G, 2, 1);
 addArc(G, 2, 3);
 addArc(G, 3, 1);
 addArc(G, 3, 2);
 printGraph(stdout, G);
 Graph TransG = transpose(G);
 printGraph(stdout, TransG);
 freeGraph(&G);				//we're done testing G so free it and its transpose
 freeGraph(&TransG);
 Graph H = newGraph(n);			//makes a new graph H
 addArc(G, 1, 3);
 addArc(G, 2, 1);
 addArc(G, 3, 2);
 printGraph(stdout, H);			//prints out contents of H without having used any other functions on it
 Graph TransH = transpose(H);		//does transpose on H
 printGraph(stdout, TransH);		//prints out transpose of H
 freeGraph(&H);				//frees H and H transpose for memory leakage
 freeGraph(&TransH);
 return(0);

}

