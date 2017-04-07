#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

sll *newSLL(void (*d)(FILE *,void *)) //d is the display function
{
    sll *items = malloc(sizeof(sll));
    if (items == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->head = 0;
    items->tail = 0;
    items->size = 0;
    items->display = d;
    return items;
}

void insertSLL(sll *items,int index,void *value)
{
	sllnode *p = malloc(sizeof(sllnode));  //New node created
    p->value = value;     //New node value assigned
    p->next = NULL;

    //Inserting at head
    if(index == 0 && items->size == 0)
    {
	   	p->next = items->head;
	   	items->head = p;
	   	items->tail = p;
	   	
	}
	else if(index == 0 && items->size> 0)
	{
		p->next = items->head;
		items->head = p;
		
	}
	//Done inserting at head

	//Inserting tail
	else if(index == items->size)
	{
		p->next = NULL;
		items->tail->next = p;
		items->tail = p;
		
	}
	//Done inserting tail

	//Inserting between head and tail
	else
	{
		int i;
		sllnode *prev = items->head;
		for (i = 0; i < index-1 ; ++i)
		{
			prev = prev->next;
		}
		p->next = prev->next;
		prev->next = p;
	
	}
	//Done inserting between head and tail
	items->size++;
	return;
}

void *removeSLL(sll *items,int index)
{
	//Remove Head
	if(index==0 && items->size!= 0)
	{
		sllnode *temp = items->head;
		void *headval = items->head->value;

		items->head = items->head->next;

		free(temp);
		
		items->size--;
		return headval;
	}
	//Remove Tail
	else if(index == items->size-1)
	{
		int i=0;
		void *tailval = items->tail->value;

		sllnode *temp = items->head;
		
		for (i = 0; i < index-1; ++i)
		{
			temp = temp->next;
		}
		items->tail = temp;
		sllnode *temp1 = temp->next;

		items->tail->next = NULL;

		free(temp1);
		
		items->size--;
		return tailval;
	}
	//Remove between head and tail
	else
	{
		int i = 0;
		sllnode *temp = items->head;

		for (i = 0; i < index-1; ++i)
		{
			temp = temp->next;
		}
		sllnode *removeNode = temp->next;
		void* removeVal = removeNode->value;

		temp->next = removeNode->next;
		free(removeNode);
		
		items->size--;
		return removeVal;

	}
	
	return 0;
}

void unionSLL(sll *recipient,sll *donor)
{
	if(donor->size == 0)
	{
		return;
	}
	else if(recipient->size != 0)
	{
		recipient->tail->next = donor->head;
		recipient->tail = donor->tail;
		recipient->size = recipient->size + donor->size;
	}
	else if(recipient->size == 0)
	{
		recipient->head = donor->head;
		recipient->tail = donor->tail;
		recipient->size = recipient->size + donor->size;
	}
	donor->head = NULL;
	donor->tail = NULL;
	donor->size = 0;
}

void *getSLL(sll *items,int index)
{
	int count = 0;
	sllnode *temp = items->head;
	while(count < index)
	{
		count++;
		temp = temp ->next;
	}
	return temp->value;
}

int sizeSLL(sll *items)
{
	return items->size;
}

void displaySLL(FILE *fp, sll *items)
{
	sllnode *temp;
	temp = items->head;

	fprintf(fp,"[");
	while(temp != NULL)
	{
		items -> display(fp,temp->value);
		if(temp->next != NULL)
		{
			fprintf(fp,",");
		}
		temp = temp -> next;
	}
	fprintf(fp,"]");
}

void *getTail(sll *items)
{
	return items->tail->value;
}

void *getHead(sll *items)
{
	return items->head->value;
}