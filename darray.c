#include <stdio.h>
#include <stdlib.h>
#include "darray.h"

struct DArray
{
    void **array; //an array of void pointers
    int capacity; //total number of slots
    int size; //number of filled slots
    void (*display)(FILE *,void *);
};

DArray *newDArray(void(*dis)(FILE *,void *))
{
    DArray *d = malloc(sizeof(DArray));

    d->array = malloc(sizeof(void *)*1);
    d->capacity = 1;
    d->size = 0;
    d->display = dis;
    d->array[0] = NULL;
    return d;
}

void insertDArray(DArray *a,void *v)
{
    if (a->size == a->capacity)
    {
        a->array = realloc(a->array,sizeof(void *) * a->capacity *2);
        a->capacity *= 2;  
    }
    a->array[a->size] = v;
    a->size++;
}

void *removeDArray(DArray *a)
{
    void *removed = a->array[a->size-1];
    a->array[a->size-1]=NULL;
    a->size--;

    if (a->capacity > 2 && a->capacity/4 > a->size)
    {
        a->array = realloc(a->array,sizeof(void *) * (a->capacity/2));
        a->capacity /= 2;
    }

    return removed;
}

void *getDArray(DArray *a,int index)
{
    return a->array[index];
}

void setDArray(DArray *a, int index, void *value)
{
    if (a->size == index)
    {
        return insertDArray(a,value);
    }
    else
    {
        a->array[index] = value;
    }
}

int sizeDArray(DArray *a)
{
    return a->size;
}

void displayDArray(FILE *fp,DArray *a)
{
    int i;
    fprintf(fp,"[");
    for (i = 0; i < a->size; ++i)
    {
        a->display(fp,a->array[i]);
        if (!(a->size-1 == i))
        {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "][%d]", a->capacity-a->size);
}

//Need to comment out this function before submission
int capDArray(DArray *a)
{
    return a->capacity;
}