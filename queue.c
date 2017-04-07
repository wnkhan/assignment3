#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "queue.h"
#include "sll.h"

queue *newQueue(void (*d)(FILE *,void *)) //d is the display function
{
    queue *items = malloc(sizeof(queue));
    if (items == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
   	items->list = newSLL(d);
   	return items;
}

void enqueue(queue *items,void *value)
{
	insertSLL(items->list,sizeSLL(items->list),value);
}

void *dequeue(queue *items)
{
	return removeSLL(items->list,0);
}
void *peekQueue(queue *items)
{
	return getSLL(items->list,0);
}

int sizeQueue(queue *items)
{
	return sizeSLL(items->list);
}

void displayQueue(FILE *fp,queue *items)
{
	displaySLL(fp, items->list);
}