//Ian Feekes
//#1474914
//ifeekes@ucsc.edu
//pa4
//findPath.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "List.h"
#define MAX_LEN 300

int main(int argc, char* argv[])
{
 FILE *input, *output;						//files are called input and output
 char lineRead[MAX_LEN];  
 if (argc != 3)							//checks to see if the command line arguments are valid
 {
  printf("Usage: %s infile outfile\n Error: too many or too few arguments", argv[0]);
  exit(1);
 }
 input = fopen(argv[1], "r");
 output = fopen(argv[2], "w");   
 if (input == NULL)						//checks to see if the file to be read from is readable
 {
  printf("ERROR: Unable to read a null file %s\n", argv[1]);
  exit(1);
 }
 if (output == NULL)
 {								//checks to see if the file to write to exists
  printf("ERROR: Unable to write to a null file %s\n", argv[2]);
  exit(1);
 }
 fgets(lineRead, MAX_LEN, input);
 char *tok; 							//array of token characters for parsing
 tok =  strtok(lineRead," \n");
 int size = atoi(tok);
 Graph G = newGraph(size);
 while(fgets(lineRead, MAX_LEN, input) != NULL)
 {
  tok = strtok(lineRead, " ");
  int u = atoi(tok);						
  tok = strtok(NULL, " ");
  int v = atoi(tok);
  if(u != 0 && v != 0) addEdge(G, u, v);
  else break;							//if we have read all the edges and translated
 }
 printGraph(output, G);
 List list = newList();
 while(fgets(lineRead, MAX_LEN, input) != NULL)
 {
  tok = strtok(lineRead, " ");
  int u = atoi(tok);
  tok = strtok(NULL, " "); 
  int v = atoi(tok);
  if( u == 0 && v == 0 ) break;					//if we have gone through all the edges
  BFS(G, u);
  int dist = getDist(G, v);
  fprintf(output, "\n");
  if(dist == -100)						//if no shortest path exists
  {
   fprintf(output, "The distance from %d to %d is infinite\n", u , v);
   fprintf(output, "No shortest path exists from %d to %d \n", u, v); 
  }
  else
  {
   fprintf(output, "The distance from %d to %d is %d\n", u, v, dist);
   fprintf(output, "A shortest %d-%d path is: ", u, v);
   getPath(list, G, v);
   printList(output, list);
   fprintf(output, "\n");
  }
  clear(list);
 }
 fclose(output);						//frees memory and the files
 fclose(input);
 freeList(&list);
 freeGraph(&G);
 return 0;    
}

