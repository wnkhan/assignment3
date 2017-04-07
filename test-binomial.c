#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "queue.h"
#include "darray.h"
#include "binomial.h"
#include "integer.h"

int main()
{

	Binomial *heap = newBinomial(displayInteger,compareInteger,NULL);
	fprintf(stdout,"Inserting...\n");
	insertBinomial(heap,newInteger(4));
	displayBinomial(stdout,heap);
	fprintf(stdout,"Inserting...\n");
	insertBinomial(heap,newInteger(8));
	displayBinomial(stdout,heap);
	fprintf(stdout,"Inserting...\n");
	insertBinomial(heap,newInteger(16));
	displayBinomial(stdout,heap);
	fprintf(stdout,"Inserting...\n");
	insertBinomial(heap,newInteger(5));
	displayBinomial(stdout,heap);
	fprintf(stdout,"Inserting...\n");
	insertBinomial(heap,newInteger(1));
	displayBinomial(stdout,heap);
	fprintf(stdout,"Extracting...\n");
	extractBinomial(heap);
	displayBinomial(stdout,heap);
	fprintf(stdout,"Extracting...\n");
	extractBinomial(heap);
	displayBinomial(stdout,heap);
	fprintf(stdout,"Extracting...\n");
	extractBinomial(heap);
	displayBinomial(stdout,heap);

	return 0;
}
