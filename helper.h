#include <stdio.h>
#include <stdlib.h>
#include "darray.h"
#include "binomial.h"

#ifndef HELPER_INCLUDED_
#define HELPER_INCLUDED_

extern void getDimensions(char *fileName, int *min, int *max);
// extern void getEdge(FILE *, int *edge);
extern void initMatrix(int numV, int aList[][numV]);
extern void printMatrix(int numV, int aList[][numV]);

#endif