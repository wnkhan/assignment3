#include <stdio.h>
#include <stdlib.h>
#include "binomial.h"
#include "darray.h"

#ifndef VERTEX_INCLUDED_
#define VERTEX_INCLUDED_

typedef struct Vertex{
	int key;
	int visited;
	int steps;
	int distance; //key
	struct Vertex *prev;
	struct BinomialNode *position;
}Vertex;

extern Vertex *newV(int key);
extern void updateV(void *v,BinomialNode *b);
extern int compareV(void *a, void *b);
extern void displayV(FILE *fp, void *v);
extern void getVertices(char *fileName, DArray *Vlist, int numV,int matrix [][numV]);
extern Vertex *findSource(DArray *Vlist, int min);
extern void printArray(DArray *Vlist);
extern void buildHeap(Binomial *h, DArray *d);

#endif