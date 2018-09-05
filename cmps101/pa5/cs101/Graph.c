//Ian Feekes
//#1474914
//ifeekes@ucsc.edu
//pa4
//graph.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include <errno.h>
#define TRUE 1
#define FALSE 0
#define INF -100
#define NIL -200

typedef struct GraphObj
{
 List *adjacent;
 char* color;
 int* parent;
 int* distance;
 int order;
 int size;
 int source;
}GraphObj;

typedef struct GraphObj* Graph;

//returns a pointer to a newly created graph object with n vertices and no edges 
Graph newGraph(int n)
{
 Graph G = malloc(sizeof(GraphObj));
 G->adjacent = calloc((n + 1), sizeof(List));
 G->distance = calloc((n + 1), sizeof(int));
 G->parent = calloc((n + 1), sizeof(int));
 G->color = calloc((n + 1), sizeof(char));
 for(int i = 0; i < n; i++)
 {
  G->adjacent[i] = newList();
  G->distance[i] = INF;
  G->parent[i] = NIL;
  G->color[i] = 'w';
 }
 G->size = 0;
 G->order = n;
 G->source = NIL;
 return G;
}

//frees all dynamic memory associated with the Graph *pG,then sets the handle *pG to NULL
void freeGraph(Graph* pG)
{
 Graph G = *pG;
 free(G->distance);
 free(G->parent);
 free(G->color);
 for(int i = 0; i < G->order; i++) freeList(&(G->adjacent[i]));
 free(*pG);
 *pG = NULL;
}

//returns order
int getOrder(Graph G)
{
 return G->order;
}

//returns size
int getSize(Graph G)
{
 return G->size;
}

//returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called
int getSource(Graph G)
{
 return G->source;
}

//returns the parent of vertex u in the Breadth- First tree created by BFS(), or NIL if BFS() has not yet been called
//precondition 1 <= u <= getOrder(G)
int getParent(Graph G, int u)
{
 return G->parent[u-1];
}

//returns the distance from the most recent BFS source to vertex u,or INF if BFS()has not yet been called
//precondition 1 <= u <= getOrder(G) 
int getDist(Graph G, int u)
{
 return G -> distance[u-1];
}

//appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists
//getPath() has the precondition getSource(G)!=NIL, so BFS() must be called before getPath()
//precondition 1 <= u <= getOrder(G) 
void getPath(List L, Graph G, int u)
{
 if(getSource(G) != NIL)
 {
  if(getSource(G) == u) append(L, u);
  else if(getSource(G) == NIL) append(L, NIL);
  else
  {
   getPath(L, G, getParent(G, u));
   append(L, u);
  }
 }
 else
 {
  printf("Error: Preconditions in getPath may not have been met");
  exit(1);
 }
}

//deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G)
{
 for(int i = 0; i < getOrder(G); i++)
 {
  List temp = G->adjacent[i];
  freeList(&temp);
  G->adjacent[i] = newList();
  G->distance[i] = INF;
  G->parent[i] = NIL;
  G->color[i] = 'w';
 }
 G->source = NIL;
 G->size = 0;
 G->order = 0;
}

//inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u
//precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v)
{
 if(u >= 1 && u <= getOrder(G) && v >= 1 && u <= getOrder(G))
 {
  addArc(G, u, v);
  addArc(G, v, u);
 }
 else
 {
  printf("Error: Preconditions in addEdge may not have been met");
  exit(1);
 }
}

//inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
//precondition that their two int arguments must lie in the range 1 to getOrder(G)
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
  printf("Error: Preconditions in addArc may not have been met");
  exit(1);
 }
}

//runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s)
{
 for(int i = 0; i < getOrder(G); i++)
 {
  G->color[i] = 'w';
  G->distance[i] = INF;
  G->parent[i] = NIL;
 }
 G->color[s - 1] = 'g';
 G->parent[s - 1] = NIL;
 G->distance[s- 1] = 0;
 G->source = s;
 List queue = newList();
 prepend(queue, s);
 while(length(queue) != 0)
 {
  int u = front(queue);
  deleteFront(queue);
  moveTo(G->adjacent[u - 1], 0);
  for(int i = 0; i < length(G->adjacent[u - 1]); i++)
  {
   int v = getElement(G->adjacent[u - 1]);
   moveNext(G->adjacent[u - 1]);
   if(G->color[v - 1] == 'w')
   {
    G->color[v - 1] = 'g';
    G->distance[v - 1] = G->distance[u - 1] + 1;
    G->parent[v - 1] = u;
    append(queue, v);
   }
  }
  G->color[u - 1] = 'b';
 }
 freeList(&queue);
}

//prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G)
{
 for(int i = 0; i < getOrder(G); i++)
 {
  fprintf(out, "%d: ", i + 1);
  printList(out, G->adjacent[i]);
  fprintf(out, "\n");
 }
}

