#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "darray.h"
#include "binomial.h"
#include "sll.h"
#include "queue.h"
#include "integer.h"
#include "scanner.h"
#include "vertex.h"
#include "helper.h"

void Dijkstra(Vertex *src, Binomial *heap, DArray *Vlist, int numV, int aList[][numV]);
void displaySPT(queue *visited);

int main(int argc,char *argv[])
{
	if (argc != 2)
	{
		fprintf(stdout,"Not correct number of command line arguments");
	}

	int maxV = 0, minV = INT_MAX;

	getDimensions(argv[1], &maxV, &minV);

	//printf("Min: %d Max: %d\n", minV, maxV);
	maxV = maxV + 1;
	int adjMatrix[maxV][maxV];

	initMatrix(maxV,adjMatrix);
	//printMatrix(maxV,adjMatrix);
	
	DArray *Vlist = newDArray(displayInteger);
	getVertices(argv[1],Vlist, maxV, adjMatrix);
	//printArray(Vlist);
	//printMatrix(maxV,adjMatrix);

	Vertex *src = findSource(Vlist, minV);

	Binomial *heap = newBinomial(displayV,compareV,updateV);

	buildHeap(heap,Vlist);
	//displayBinomial(stdout,heap);

	Dijkstra(src, heap, Vlist, maxV, adjMatrix);

	return 0;
}
//Dijkstra's basic outline was provided in the CS201 forum that can
//be found on the course website.
void Dijkstra(Vertex *src, Binomial *heap, DArray *Vlist, int numV, int aList[][numV])
{
	queue *visited = newQueue(displayV);
	src->distance = 0;
    src->prev = src;
    src->steps =  0;

    while(sizeBinomial(heap)!=0)
    {
    	Vertex *u = (Vertex *) extractBinomial(heap);

    	if (u->prev == NULL)
    	{
    		u->distance = 0;
    		displaySPT(visited);
    		visited = newQueue(displayV);
    	}
    	enqueue(visited, u);
    	u->visited = 1;
    	for (int i = 0; i < numV; ++i)
    	{
    		if (aList[u->key][i]!= 0)
    		{	
    			int edgeWt = aList[u->key][i];
    			Vertex *v = getDArray(Vlist,i);
    			if (v->visited != 1)
    			{
    				int distance = u->distance + edgeWt;
    				if (distance < v->distance)
    				{
    					v->prev = u;
    					v->distance = distance;
    					v->steps = v->prev->steps + 1;
    					decreaseKeyBinomial(heap,v->position,v);
    				}
    			}
    		}
    	}
    }
    displaySPT(visited);
}
//A method for displaying the spanning 
//tree was also provided in the beastie
//forums.
void displaySPT(queue *visited) {
     if(sizeQueue(visited) == 0) return;

     Binomial *b = newBinomial(displayV, compareV, updateV);
     int qsize = sizeQueue(visited);
     int maxSteps = 0;

     int i = 0;
     for(i = 0; i < qsize; i++) {
          Vertex *v =  (Vertex *) dequeue(visited);
          if(v->steps > maxSteps) maxSteps = v->steps;
          insertBinomial(b, v);
     }
     queue *level[maxSteps];
     for(i = 0; i <= maxSteps; i++) {
          level[i] = newQueue(displayV);
     }

     for(i = 0; i < qsize; i++) {
          Vertex *v = (Vertex *) extractBinomial(b);
          enqueue(level[v->steps], v);
     }
     for(i = 0; i <= maxSteps; i++) {
          fprintf(stdout, "%d : ", i);
          while(sizeQueue(level[i]) != 0) {
               Vertex *v = (Vertex *) dequeue(level[i]);
               displayV(stdout, v);
               if(sizeQueue(level[i]) > 0) fprintf(stdout, " ");
          }
          fprintf(stdout, "\n");
     }
     fprintf(stdout, "----\n");
}
