#define _CRT_SECURE_NO_DEPRECATE
//done visual2013 which dosen't like depecrated stuff...
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

//simple edge
typedef struct {
	int v1;
	int v2;
	float weight;
} Edge;

//list of edges in the graph
struct list_edge {
	Edge edge;
	struct list_edge * next;
};

//external variables, I'll give the actual definition in a sparate header and include it just inside boruvka.cpp
extern list_edge * curr, *head, *mstTree;
extern int number_of_runs;
extern int number_vertexs;
extern int number_edges;
extern int* root;
extern int* rank;

//Print graph details
void printData(list_edge * list);

//Read and initialize graph components
void initGraph(FILE * pFile);

//find root for a node
int findRoot(int i);

// make root of the node with a smaller rank point to root of the node with a larger rank
void unionEdge(int i, int j);

//boruvka algorithm
void boruvkaMst();