#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "scanner.h"
#include "vertex.h"
#include "darray.h"
#include "binomial.h"
#include "helper.h"

Vertex *newV(int key) {
	Vertex *v = malloc(sizeof(Vertex));
	v->key = key;
	v->visited = 0;
	v->steps = 0;
	v->distance = INT_MAX;
	v->prev = NULL;
	v->position = NULL;
	return v;
}
//Compare, display, and update were modeled in 
//accordance with a discussion that 
//took place with classmates on the proper
//way to handle the vertex type to be used for Dikj.
void updateV(BinomialNode *b, void *v)
{
	Vertex *V = v;
	V->position = b;
}

//This compare function was a 
int compareV(void *a, void *b) {
     if(a == NULL && b == NULL) return 0;
     else if(a == NULL) return -1;
     else if(b == NULL) return 1;

     Vertex *x = (Vertex *) a;
     Vertex *y = (Vertex *) b;
     if(x->distance == y->distance) {
          if(x->key < y->key) {
               return -1;
          } else {
               return 1;
          }
     } else if(x->distance < y->distance) {
          return -1;
     } else {
          return 1;
     }
}

void displayV(FILE *fp, void *value)
{
	Vertex *v = (Vertex *) value;
	fprintf(fp, "%d", v->key);
     if(v->prev != NULL && v->prev != v) 
     {
          fprintf(fp, "(%d)", v->prev->key);
          fprintf(fp, "%d", v->distance);
     }
     return;
}

void getVertices(char *fileName, DArray *Vlist, int numV, int aList[][numV])
{
	FILE *inputFile = NULL;

	inputFile = fopen(fileName,"r");
	
	char *V1,*V2,*E;
	int v1, v2, edge;

	while(v1!=EOF)
	{
		V1 = readToken(inputFile);
		if (V1==0)
		{
			break;
		}
		V2 = readToken(inputFile);
		E = readToken(inputFile);

		if (strcmp(E,";") == 0)
		{
			v1 = atoi(V1);
			v2 = atoi(V2);
			edge = 1;
		}
		else
		{
			v1 = atoi(V1);
			v2 = atoi(V2);
			edge = atoi(E);
			readToken(inputFile);
		}
		printf("v1 %d\t v2 %d\t edge %d\n", v1,v2,edge);
		if (aList[v1][v2] == 0  || aList[v2][v1]==0)
		{
			aList[v1][v2] = edge;
			aList[v2][v1] = edge;
		}
		else
		{
			if (edge<aList[v1][v2] || edge<aList[v2][v1])
			{
				aList[v1][v2] = edge;
				aList[v2][v1] = edge;
			}
		}
		
		
	}
	fclose(inputFile);
	return;
}