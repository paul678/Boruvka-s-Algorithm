#include "variableDefinitions.h"

void printData(list_edge * list) 
{
	list_edge *a = list;
	float cost = 0;
	while (a->next != NULL) 
	{
		printf("%d----%d  weight: %.2f\n", a->edge.v1, a->edge.v2, a->edge.weight);
		cost += a->edge.weight;
		a = a->next;
	}
	printf("And has a cost of: %.2f\n", cost);
}

void initGraph(FILE * pFile)
{
	int i;
	head = NULL;
	fscanf(pFile, "%d", &number_vertexs);
	fscanf(pFile, "%d", &number_edges);
	
	root = (int*)malloc(number_vertexs * sizeof(int));
	rank = (int*)malloc(number_vertexs * sizeof(int));
	head = (list_edge*)malloc(sizeof(list_edge));
	curr = head;
	for (i = 0; i < number_edges; i++)
	{
		list_edge * newEdge = (list_edge*)malloc(sizeof(list_edge));
		fscanf(pFile, "%d", &curr->edge.v1);
		fscanf(pFile, "%d", &curr->edge.v2);
		fscanf(pFile, "%f", &curr->edge.weight);
		newEdge->next = NULL;
		curr->next = newEdge;
		curr = newEdge;
	}

	//init root and rank vectors
	for (i = 0; i < number_vertexs; i++) 
	{
		root[i] = i;
		rank[i] = 1;
	}
}
int findRoot(int i) 
{
	while (i != root[i]) 
	{
		i = root[i];
	}
	return i;
}

void unionEdge(int i, int j) 
{

	if (i == j) 
	{
		return;
	}

	// make smaller root point to larger one
	if (rank[i] < rank[j]) 
	{
		root[i] = j;
		rank[j] += rank[i];
	}
	else 
	{
		root[j] = i;
		rank[i] += rank[j];
	}
}
void boruvkaMst() 
{
	list_edge *tree;
	Edge* closest = (Edge *)malloc(number_vertexs * sizeof(Edge));
	mstTree = (list_edge*)malloc(sizeof(list_edge));
	tree = mstTree;
	int mstTreeSize = 0;
	int countEdge = 0;
	int iterationCount = 0;
	do {
		for (int i = 0; i < number_vertexs; i++) 
		{
			closest[i].weight = -1;
		}
		curr = head;
		//find closest edge
		while (curr->next != NULL)
		{
			int i = findRoot(curr->edge.v1);
			int j = findRoot(curr->edge.v2);
			if (i == j) 
			{
				curr = curr->next;
				continue;
			}
			if (closest[i].weight == -1 || curr->edge.weight < closest[i].weight) 
			{
				closest[i] = curr->edge;
			}
			if (closest[j].weight == -1 || curr->edge.weight < closest[j].weight) 
			{
				closest[j] = curr->edge;
			}
			curr = curr->next;
		}
		countEdge = 0;
		for (int i = 0; i < number_vertexs; i++) 
		{
			Edge e = closest[i];
			if (e.weight != -1) {
				int u = findRoot(e.v1);
				int v = findRoot(e.v2);
				if (u != v) 
				{
					countEdge++;
					list_edge* newEdge = (list_edge*)malloc(sizeof(list_edge));
					tree->edge = e;
					tree->next = newEdge;
					tree = newEdge;
					mstTreeSize++;
					unionEdge(u, v);
				}
			}
		}
		iterationCount++;
	} while (mstTreeSize < number_vertexs - 1);
	tree->next = NULL;
	printf("was found in: %d iteration(s) \n", iterationCount);
}