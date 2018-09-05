//Ian Feekes
//#1474914
//ifeekes@ucsc.edu
//pa5
//findComponents.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"
#define MAX_LEN 300

int main(int argc, char* argv[])
{
 FILE *input, *output;
 char lineRead[MAX_LEN];
 if (argc != 3)										//checks to see if the command line arguments are accurate
 {
  printf("Usage: %s infile outfile\n Error: incorrect formatting of command line arguments", argv[0]);
  exit(1);
 }
 input = fopen(argv[1], "r");								//opens input file 
 output = fopen(argv[2], "w");								//opens output file

 if(input == NULL)									//makes sure the files aren't null
 {
  printf("ERROR: cannot read  %s\n", argv[1]);
  exit(1);
 }
 if(output == NULL)
 {
  printf("ERROR: cannot write  %s\n", argv[2]);
  exit(1);
 }
 
 fgets(lineRead, MAX_LEN, input);
 char *tok; 
 tok =  strtok(lineRead," \n");
 int size = atoi(tok);
 Graph G = newGraph(size);
 List S = newList();
 for (int i = 1; i <= size; i++)append(S, i);
 while(fgets(lineRead, MAX_LEN, input) != NULL)
 {
  tok = strtok(lineRead, " ");
  int u = atoi(tok);
  tok = strtok(NULL, " ");
  int v = atoi(tok);
  if(u != 0 && v != 0) addArc(G, u, v);
  else break;      
 }   
 fprintf(output, "Adjacency representation of G:\n");
 printGraph(output, G);
 fprintf(output, "\n");
 DFS(G, S);
 Graph T = transpose(G);
 DFS(T, S);
 int pos = length(S) - 1;
 int numSCC = 0;
 for(int i = 0; i < size; i++)
 {
  if(getParent(T, i) == 0) numSCC++;							//numSCC = number of strongly-connected components
 }
 fprintf(output, "G contains %d strongly connected components: \n", numSCC);
 List temp = newList();
 moveTo(S, length(S)-1);
 int start = 1;
 for(int i = 0; i < getOrder(G); i++)
 {
  prepend(temp, getElement(S));
  if(getParent(T, getElement(S)) == 0)
  {
   fprintf(output, "Component %d: ", start);
   printList(output, temp);
   fprintf(output, "\n");
   clear(temp);
   start++;
  }
  moveTo(S, --pos);
 }    
 		   
 freeGraph(&G);										//frees graphs, lists, and closes files to stop memory leakage
 freeGraph(&T);
 freeList(&S);
 fclose(output);
 fclose(input);
 return 0;    
}

