#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__

    typedef struct queue
        {
        struct sll *list;
        } queue;

extern queue *newQueue(void (*d)(FILE *,void *));   //constructor
extern void enqueue(queue *items,void *value);      //stores a generic value
extern void *dequeue(queue *items);                 //returns a generic value
extern void *peekQueue(queue *items);               //returns a generic value
extern int sizeQueue(queue *items);
extern void displayQueue(FILE *,queue *items);

#endif