#include "Graph.h"
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj
{
	int order; 
	int size;
	int * parent;
	int * color; 
	int * discovered;
	int * finished;
	List *adjList;
} GraphObj;

Graph newGraph(int n)
{ 
	if(n <=0) fprintf(stderr, "Error: graph initialized with illegal amount of vertices\n");
	Graph G = malloc(sizeof(GraphObj));
	G->adjList = malloc(n*sizeof(List));
	G->order = n;
	G->size=0;
	G->discovered = malloc(n*sizeof(int));
	G->finished = malloc(n*sizeof(int));
	G->parent=malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
	{
		G->parent[i]=NIL;
 		G->adjList[i]=newList();
		G->finished[i]=-1;
		G->discovered[i]=-1;
	}
	return G;
}

void freeGraph(Graph* pG)
{
	if(!*pG==NULL)
	{
		for(int i=0;i<(pG)->order;i++)freeList(&(*pG)->adjList[i]);
		free((*pG)->parent);
		(*pG)->parent = NULL;
		free((*pG)->color);
		free((*pG)->adjList);
		free((*pG)->discovered);
		free((*pG)->finished);
		(*pG)->color = NULL;
		(*pG)->adjList = NULL;
		(*pG)->discovered = NULL;
		(*pG)->finished = NULL;
		free(*pG);
		*pG = NULL;
	}
	else 
	{
		fprintf(stderr, "Error: cannot free a null graph\n");
		exit(1);
	}
}

int getOrder(Graph G)
{
	if(G!=NULL) return G->order;
	else
	{
		fprintf(stderr, "Error: cannot get order of a null graph\n");
		exit(1);
	}
}

int getSize(Graph G)
{
	if(G!=NULL) return G->size;
        else
        {
                fprintf(stderr, "Error: cannot get size of a null graph\n");
                exit(1);
        }
}

int getParent(Graph G, int u)
{
	if(G!=NULL&& G->parent!=NULL) return G->parent[--u];
        else
        {
                fprintf(stderr, "Error: cannot get parent of a null graph\n");
                exit(1);
        }
}

int getDiscover(Graph G, int u)
{
  	if(G == NULL|| u<1 || u > G->order) 
	{
    		fprintf(stderr, "Error : cannot discover null graph or invalid vertex");
   		exit(1);
  	}
  	return G->discovered[--u];
}

int getDiscover(Graph G, int u) 
{
        if(G == NULL|| u<1 || u > G->order)
        {
                fprintf(stderr, "Error : cannot finish null graph or invalid vertex");
                exit(1);
        }
        return G->finished[--u];
}

void makeNull(Graph G) 
{ 
	if(G == NULL)
	{
  		fprintf(stderr, "Graph null in make null");
 		 exit(1);
	}
	for(int i = 0; i < G->order; i++) clear(G->adj_list[i]);
}

void addEdge(Graph G, int u, int v)
{
	if(G == NULL) 
	{
  		fprintf(stderr, "Graph null in addEdge");
    		exit(1);
  	}
  	else if(u > G->order || v > G->order || u <= 0 || v <= 0)
	 {
    		fprintf(stderr, "Error : Invalid index, out of range (addEdge function)");
    		exit(1);
  	}
  	--u;
	--v;
  	insertSorted(G->adj_list[u], v);
  	insertSorted(G->adj_list[v], u);
}

void addArc(Graph G, int u, int v)
{
  	if(G == NULL) 
	{
    		fprintf(stderr, "Graph null in addArc");
   		 exit(1);
  	}
  	else if(u > G->order || v > G->order || u <= 0 || v <= 0)
	{
    		fprintf(stderr, "Error : Invalid index, out of range (addArc function)");
    		exit(1);
  	}
  	--u;
	--v;
  	insertSorted(G->adj_list[u], v);
}

void printGraph(FILE* out, Graph G)
{  
  	if(G == NULL || out == NULL)
	{
    		fprintf(stderr, "Error : Null input in printGraph");
    		exit(1); 
  	}
 	for(int i = 0; i < G->order; i++)
	{
    		List L = G->adj_list[i];
    		fprintf(out, "%d :", i+1);
    		for(moveTo(L, 0); getIndex(L) >= 0; moveNext(L)) fprintf(out, " %d ", getElement(L)+1);
    		fprintf(out, "\n");
  	}
}

Graph copyGraph(Graph G)
{
 	Graph new_graph = newGraph(G->order);
  	for(int i = 0; i < G->order; i++) 
	{
    		List * temp = &G->adj_list[i];
    		for(moveTo(*temp, 0); getIndex(*temp) >= 0; moveNext(*temp))addArc(new_graph, i+1, getElement(*temp)+1);
  	}
  	return new_graph;
}

Graph transpose(Graph G)
{
	Graph new_graph = newGraph(G->order);
	for(int i = 0; i < G->order; i++)
	{
    		List * temp = &G->adj_list[i];
    		for(moveTo(*temp, 0); getIndex(*temp) >= 0; moveNext(*temp))addArc(new_graph, getElement(*temp)+1, i+1);
  	}
  	return new_graph;
}

void visit(Graph G, List s, int vert, int * t) {
  G->color[vert] = GRAY;
  G->discovered[vert] = ++(*t);
  for(moveTo(G->adj_list[vert], 0); getIndex(G->adj_list[vert]) >= 0; moveNext(G->adj_list[vert])) {
    
    int curr = getElement(G->adj_list[vert]);
    if(G->color[curr] == WHITE) {
      G->parent[curr] = vert+1;
      visit(G, s, curr, t);
    }
  }

  G->color[vert] = BLACK;
  G->finished[vert] = ++(*t);
  prepend(s, vert);
}

void DFS(Graph G, List s) {

  if(G == NULL) {
    fprintf(stderr, "Error : Null input in DFS");
    exit(1); 
  }

  if(length(s) != G->order) {
    fprintf(stderr, "Precondition Failure : List length != G->order in DFS");
    exit(1); 
  }

  List ret = newList();
for(int i = 0; i < G->order; i++) {
    G->color[i] = WHITE;
    G->parent[i] = NIL;
  }

  int t = 0;
for(moveTo(s, 0); getIndex(s) >= 0; moveNext(s)) {
    int curr = getElement(s)-1;
    if(G->color[curr] == WHITE) {
      visit(G, ret, curr, &t);
    }  
  }

  clear(s);
  for(moveTo(ret, 0); getIndex(ret) >= 0; moveNext(ret)) {
      append(s, getElement(ret)+1);
  }

  freeList(&ret);

}
