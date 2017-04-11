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

int main(int argc,char *argv[])
{
	if (argc != 2)
	{
		fprintf(stdout,"Not correct number of command line arguments");
	}

	int maxV = 0, minV = INT_MAX;

	getDimensions(argv[1], &maxV, &minV);

	printf("Min: %d Max: %d\n", minV, maxV);
	maxV = maxV + 1;
	int adjMatrix[maxV][maxV];

	initMatrix(maxV,adjMatrix);
	//printMatrix(maxV,adjMatrix);
	
	DArray *Vlist = newDArray(displayInteger);
	getVertices(argv[1],Vlist, maxV, adjMatrix);
	printMatrix(maxV,adjMatrix);




	return 0;
}

