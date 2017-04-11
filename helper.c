#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "scanner.h"

void getDimensions(char *fileName, int *max, int *min)
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
		//Find maximum
		if (v1 > v2)
		{
			if (v1>*max) *max = v1;
		}
		else 
		{
			if(v2>*max) *max = v2;
		}
		//Find minimum
		if (v1 < v2)
		{
			if (v1<*min) *min = v1;
		}
		else 
		{
			if(v2<*min) *min = v2;
		}
	}

	fclose(inputFile);
	return;
}

void initMatrix(int numV, int aList[][numV])
{
	//Initialize adjMatrix to all 0's
	int i, j;  
	for (i = 0; i < numV; ++i)
	{
		for (j = 0; j < numV; ++j)
		{
			aList[i][j] = 0;
		}
	}
}

void printMatrix(int numV, int aList[][numV])
{
	int i, j;
	for (i = 0; i < numV; ++i)
	{
		for (j = 0; j < numV; ++j)
		{
			printf("%d ", aList[i][j]);
		}
		printf("\n");
	}
}



// void getEdge(FILE *input, int *edge)
// {	
// 	char *V1,*V2,*E;

// 	V1 = readToken(input);
// 	if (V1==0)
// 	{
// 		return;
// 	}
// 	V2 = readToken(input);
// 	E = readToken(input);

// 	if (strcmp(E,";") == 0)
// 	{
// 		edge[0] = atoi(V1);
// 		edge[1] = atoi(V2);
// 		edge[2] = 1;
// 	}
// 	else
// 	{
// 		edge[0] = atoi(V1);
// 		edge[1] = atoi(V2);
// 		edge[2] = atoi(E);
// 		readToken(input);
// 	}
// }