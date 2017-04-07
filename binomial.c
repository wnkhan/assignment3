#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "sll.h"
#include "darray.h"
#include "binomial.h"

void merge(Binomial *b, DArray *donor);
BinomialNode *bubbleUp(Binomial *b, BinomialNode *n);
void consolidate(Binomial *b, BinomialNode *n);
BinomialNode *combine(Binomial *b, BinomialNode *x, BinomialNode *y);
void updateExtreme(Binomial *b, BinomialNode *n);
void findExtreme(Binomial *b);
void printSubHeaps(FILE *fp, BinomialNode *n);
BinomialNode *getSubHeap(DArray *array, int degree);


struct BinomialNode
{
	void *value;
	DArray *children;
	struct BinomialNode *parent;
	void (*display)(FILE *, void *);
};

BinomialNode *newBinomialNode(void (*display)(FILE *, void *), void *value)
{
	BinomialNode *n = malloc(sizeof(BinomialNode));

	n->display = display;
	n->value = value;
	n->children = newDArray(display);
	n->parent = n;
	return n;
}

void displayBinomialNode(FILE *fp,BinomialNode *n)
{
	n->display(fp,n->value);
	fprintf(fp, "-%d", sizeDArray(n->children));

	if (n->parent != n)
	{
		fprintf(fp, "(");
		n->display(fp,n->parent->value);
		fprintf(fp, "-%d)", sizeDArray(n->parent->children));
	}
}

struct Binomial
{
	DArray *rootlist;
	int (*compare)(void *,void *);
	void (*update)(void *,BinomialNode *);
	BinomialNode *extreme;
	int size;
	void (*display)(FILE *,void *);
};

Binomial *newBinomial(void (*d)(FILE *,void *),int (*c)(void *,void *),        
    void (*u)(void *,BinomialNode *))
{
	Binomial *b = malloc(sizeof(Binomial));

	b->display = d;
	b->compare = c;
	b->update = u;
	b->rootlist = newDArray(d);
	b->size = 0;
	b->extreme = NULL;
	return b;
}

BinomialNode *insertBinomial(Binomial *b,void *value)
{
	BinomialNode *n = newBinomialNode(b->display,value);
	n->value = value;
	n->parent = n;
	n->children = newDArray(n->display);
	updateExtreme(b,n);
	consolidate(b,n);
	b->size++;
	return n;
}

int sizeBinomial(Binomial *b)
{
	return b->size;
}

void deleteBinomial(Binomial *b,BinomialNode *n)
{
	decreaseKeyBinomial(b,n,NULL);
	extractBinomial(b);
}

void decreaseKeyBinomial(Binomial *b, BinomialNode *n, void *value)
{
	n->value = value;
	BinomialNode *bubble = bubbleUp(b,n);
	if (bubble->parent == bubble)
	{
		updateExtreme(b,bubble);
	}
}

void *extractBinomial(Binomial *b)
{ 
	BinomialNode *y = b->extreme;

	//finds index of y in the rootlist
	int i;
	for (i = 0; i < sizeDArray(b->rootlist); ++i)
	{
		if (y==getDArray(b->rootlist,i))
		{
			setDArray(b->rootlist,i,NULL);
		}
	}
	
	merge(b,y->children);
	
	b->size--;
	void *temp = y->value;
	free(y);
	findExtreme(b);

	return temp;
}

void displayBinomial(FILE *fp, Binomial *b) {
     if(b->size == 0) {
          fprintf(fp, "0:\n");
          return;
     }

     int index = 0;
     for(index = 0; index < sizeDArray(b->rootlist); index++) {
          if(getSubHeap(b->rootlist, index) != NULL) {
               printSubHeaps(fp, (BinomialNode *) getSubHeap(b->rootlist, index));
               fprintf(fp, "----\n");
          }
     }
}

/////////////////Helper functions/////////////////////////////

void printSubHeaps(FILE *fp, BinomialNode *n) {
     queue *q = newQueue(n->display);
     enqueue(q, n);
     enqueue(q, NULL);
     int level = 0;
     fprintf(fp, "%d: ", level);
     while(sizeQueue(q) != 0) {
          BinomialNode *temp = dequeue(q);
          if(temp == NULL) {
               fprintf(fp, "\n");
               if(sizeQueue(q) != 0) {
                    ++level;
                    enqueue(q, NULL);
                    fprintf(fp, "%d: ", level);
               }
          } else {
               displayBinomialNode(fp, temp);
               if(peekQueue(q) != NULL) fprintf(fp, " ");
               int index = 0;
               for(index = 0; index < sizeDArray(temp->children); index++) {
                    enqueue(q, (BinomialNode *) getSubHeap(temp->children, index));
               }
          }
     }
}

BinomialNode *getSubHeap(DArray *array, int degree) {
     if(degree > sizeDArray(array)) {
          fprintf(stderr, "Error in getSubHeap!\n");
          exit(-1);
     } else if(degree == sizeDArray(array)) {
          return NULL;
     } else {
          return getDArray(array, degree);
     }
}

void merge(Binomial *b, DArray *donor)
{
	BinomialNode *n = NULL;
	int i;
	for (i = 0; i < sizeDArray(donor); ++i)
	{
		n = (BinomialNode *) getDArray(donor,i);
		n->parent = n;

		consolidate(b,n);
	}
	free(donor);
}

BinomialNode *bubbleUp(Binomial *b, BinomialNode *n)
{
	if (n->parent==n)
	{
		return n;
	}
	else if (b->compare(n->value,n->parent->value)> 0)
	{
		return n;
	}
	else
	{
		b->update(n->value,n->parent);
		b->update(n->parent->value,n);

		void *swap = n->value;
		n->value = n->parent->value;
		n->parent->value = swap;

		return bubbleUp(b,n->parent);
	}
}

void consolidate(Binomial *b, BinomialNode *n)
{
	int degree = sizeDArray(n->children);
	while(getSubHeap(b->rootlist,degree)!= NULL)
	{
		n = combine(b,n,getSubHeap(b->rootlist,degree));
		setDArray(b->rootlist,degree,NULL);
		++degree;
		if(degree==sizeDArray(b->rootlist))
		{
			insertDArray(b->rootlist,NULL);
		}
	}
	setDArray(b->rootlist,degree,n);
}

BinomialNode *combine(Binomial *b, BinomialNode *x, BinomialNode *y)
{
	int i = 0;
	if (b->compare(x->value,y->value)<0)
	{
		i = sizeDArray(y->children);
		setDArray(x->children,i,y);
		y->parent = x;
		return x;
	}
	else 
	{
		i = sizeDArray(x->children);
		setDArray(y->children,i,x);
		x->parent = y;
		return y;
	}
}

void updateExtreme(Binomial *b, BinomialNode *n)
{
	if (b->extreme == NULL)
	{
		b->extreme = n;
	}
	else if (b->compare(b->extreme->value,n->value)>0)
	{
		b->extreme = n;
	}
}

void findExtreme(Binomial *b)
{
	b->extreme = NULL;
	BinomialNode *n;
	int i = 0;
	for (i = 0; i < sizeDArray(b->rootlist); ++i)
	{ 
		n = getSubHeap(b->rootlist,i);
		if (n!=NULL)
		{
			updateExtreme(b,n);
		}
	}
}
///////////////////End of helper functions/////////////