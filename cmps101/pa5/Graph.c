//Ian Feekes
//ifeekes@ucsc.edu
//#1474914
//pa5
//graph.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include "Graph.h"
#define UNDEF -100
#define NIL 0


typedef struct GraphObj
{
    List *adjacent;
    char* color;
    int* parent;
    int* discover;
    int* finish;
    int order;
    int size;
    int source;
}
GraphObj;

typedef struct GraphObj* Graph;

Graph newGraph(int n)				//creates a new graph object with default properties
{   
 Graph G = malloc(sizeof(GraphObj));
// G->adjacent = calloc((n + 1), sizeof(List));
// G->discover = calloc((n + 1), sizeof(int));
// G->finish = calloc((n + 1), sizeof(int));
// G->parent = calloc((n + 1), sizeof(int));
// G->color = calloc((n + 1), sizeof(char));
 G->adjacent = malloc((n)*sizeof(List));
 G->discover = malloc((n)*sizeof(int));
G->finish = malloc((n)*sizeof(int));
G->parent = malloc((n)*sizeof(int));
G->color = malloc((n)*sizeof(char));
for(int i = 0; i < n; i++)
 {
  G->adjacent[i] = newList();
  G->discover[i] = UNDEF;
  G->finish[i] = UNDEF;
  G->parent[i] = NIL;
  G->color[i] = 'w';
 }
 G->size = 0;
 G->order = n;
 //G->source = NIL;
 return G;
}

void freeGraph(Graph* pG)
{
 if((*pG) != NULL)				//checks the precondition
 {
  free((*pG)->discover);
  free((*pG)->finish);
  free((*pG)->parent);
  free((*pG)->color);
  for(int i = 0; i < (*pG)->order; i++) freeList(&((*pG)->adjacent[i]));//frees all the lists affiliated with the graph
  free((*pG)->adjacent);
  free(*pG);
  *pG = NULL;
 }
}

int getOrder(Graph G)
{
 if (G != NULL)return G->order;
 else
 {
  fprintf(stdout, "Error: GetOrder called on a null graph G");
  exit(1);
 }
}

int getSource(Graph G)
{
 if (G != NULL)return G->source;
 else
 {
  fprintf(stdout, "G = NULL. Exiting...");
  exit(1);
 }
}

int getSize(Graph G)
{
 if (G != NULL) return G->size;
 else
 {
  fprintf(stdout, "Error: GetSize called on a null graph G");
  exit(1);
 }
}

int getParent(Graph G, int u)						//same thing as get source and getORDER
{
 if(G != NULL) return G->parent[u - 1];
 else
 {
  fprintf(stdout, "Error GetParent called on a null graph G");
  exit(1);
 }
}

int getDiscover(Graph G, int u)
{
 if(1 <= u && u <= getOrder(G)) return(G->discover[u - 1]);		//checks the precondition
 else
 {
  fprintf(stdout, "Error: getDiscover preconditions not met on graph G and int U");
  exit(1);
 }

}

int getFinish(Graph G, int u)
{
 if(1 <= u && u <= getOrder(G))return(G->finish[u - 1]);		//checks the precondition  
 else
 {
  fprintf(stdout, "Error: getFinish preconditions not met on graph G and int U");
  exit(1);
 }
}

void addArc(Graph G, int u, int v)
{
 if(u >= 1 && u <= getOrder(G) && v >= 1 && u <= getOrder(G))
 {
  int row = u - 1;
  if(length(G->adjacent[row]) == 0)
  {
   append(G->adjacent[row], v);
   G->size++;
  }
  else if(length(G->adjacent[row]) == 1)
  {
   if(front(G->adjacent[row]) > v)
   {
    prepend(G->adjacent[row], v);
    G->size++;
   }
   else
   {
    append(G->adjacent[row], v);
    G->size++;
   }
  }
  else if(length(G->adjacent[row]) >= 2)
  {
   if(front(G->adjacent[row]) > v)
   {
    prepend(G->adjacent[row], v);
    G->size++;
   }
   else if(back(G->adjacent[row]) < v)
   {
    append(G->adjacent[row], v);
    G->size++;
   }
   else
   {
    for(int i = 0; i < length(G->adjacent[row]) - 1; i++)
    {
     moveTo(G->adjacent[row], i + 1);
     int p = getElement(G->adjacent[row]);
     moveTo(G->adjacent[row], i);
     int q = getElement(G->adjacent[row]);
     if(p > v && q < v)
     {
      insertAfter(G->adjacent[row], v);
      moveNext(G->adjacent[row]);
      G->size++;
     }
     else moveNext(G->adjacent[row]);
    }  
   }
  }
 }
 else
 {
  printf("Error: preconditions for addArc function have not been met");
  exit(1);
 }
}

void addEdge(Graph G, int u, int v)
{
 if(u >= 1 && u <= getOrder(G) && v >= 1 && u <= getOrder(G))
 {
  addArc(G, u, v);
  addArc(G, v, u);
 }
 else
 {
  printf("Error: addEdge called on a graph not meeting preconditions of the function");
  exit(1);
 }
}

void DFS(Graph G, List S)
{
 if (G == NULL)
 {
  printf("Error: DFS called on a null graph");
  exit(1);
 }
 if (length(S) != getOrder(G))
 {
  printf("Error: List and Graph contain an inequal quantity of vertices");
  exit(1);
 }
 for (int i = 0; i <= getOrder(G); i++)
 {
  G->color[i] = 'w';
  G->parent[i] = NIL;
 }
 int time = 0;
 moveTo(S, length(S) - 1);
 for (int i = 0; i < getOrder(G); i++)
 {
  if(G->color[front(S) - 1] == 'w')
  {
   int x = front(S);
   time = Visit(x, G, S, time);
  }
  deleteFront(S);
 }
}


Graph transpose(Graph G)
{
 if (G != NULL)
 {
  Graph new = newGraph(getOrder(G));
  for(int i = 0; i < getOrder(G); i++)
  {
   for(int j = 0; j < length(G->adjacent[i]); j++)
   {
    moveTo(G->adjacent[i], j);
    addArc(new, getElement(G->adjacent[i]), i + 1);
   }
  }
  return(new);
 }
 else
 {
  fprintf(stdout, "Error: transpose called on a null graph G");
  exit(1);
 }
}

Graph copyGraph(Graph G)
{
 if(G != NULL)
 {
  Graph copy = newGraph(getOrder(G));
  for (int i = 0; i < getOrder(copy); i++)
  {
   copy->adjacent[i] = copyList(G->adjacent[i]);
   copy->discover[i] = getDiscover(G, i);
   copy->finish[i] = getFinish(G, i);
   copy->color[i] = G->color[i];
  }
  copy->size = getSize(G);
  copy->source = getSource(G);
  return(copy);
 }
 else
 {
  fprintf(stdout, "Erorr: copyGraph is called on a null graph G");
  exit(1);
 }
}

void printGraph(FILE* out, Graph G)
{
 if(G != NULL)
 {
  for(int i = 0; i < getOrder(G); i++)
  {
   fprintf(out, "%d: ", i + 1);
   printList(out, G->adjacent[i]);
   fprintf(out, "\n");
  }
 }
 else
 {
  fprintf(stdout, "Error: cannot print a null graph");
  exit(1);
 }
}

int Visit(int x, Graph G, List S, int time)				//helper function mentioned in the programming assignment
{
 G->color[x - 1] = 'g';
 time++;
 G->discover[x - 1] = time;
 for (int i = 0; i < length(G->adjacent[x - 1]); i++)
 {
  moveTo(G->adjacent[x - 1], i);
  int y = getElement(G->adjacent[x - 1]) - 1;
  if (G->color[y] == 'w')
  {
   G->parent[y] = x;
   time = Visit(getElement(G->adjacent[x - 1]), G, S, time);
  }
 }
 G->color[x - 1] = 'b';
 time++;
 G->finish[x - 1] = time;
 insertAfter(S, x);
 return(time);
}
