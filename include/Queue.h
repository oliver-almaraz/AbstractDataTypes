/******************************************************
*                    Queue.h
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************
*
*	C library providing an interface for creating and
*	destroying QUEUES, with functions to enqueue,
*	dequeue, to peek them.
*
*	This library is an EXTENSION of the LinkedList
*	lib provided in this repository. Therefore, you
*	should be aware of the description presented in
*	./LinkedList.h. For even more detail, you may look
*	into ./source/LinkedList.c.
*
*	Queue_init(stack) calls list_init(queue, NULL).
*	Passing NULL instead of a destroy_data() fn allows
*	the user to use the data stored in the HEAD
*	after queue_dequeue() is called: it returns a void
*	pointer to it.
*******************************************************
*	As a consecuence, the user is ALWAYS responsible
*	for freeing dyn. alloc. data after queue_dequeue()
*	is called.
*******************************************************
*
*	In the other hand, queue_destroy(), takes as its
*	second argument a function ptr to free the DATA in
*	case it was dyn. alloc. when removing all the elmts
*	in the queue. As with list_init(), you may pass
*	NULL if DATA is not dyn. alloc.
*
*	Finally, queue_peek() returns a ptr to the data of
*	the element at the head of the queue without caling
*	queue_dequeue().
*******************************************************
*	You should always check for a NULL pointer
*	when calling queue_peek() and queue_dequeue();
******************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include "LinkedList.h"

typedef List Queue;

/***********************************************
*               PUBLIC INTERFACE
***********************************************/
#define queue_alloc() (Queue*)malloc(sizeof(Queue))
#define queue_init(queue) list_init((queue), NULL)
#define queue_enqueue(queue, data) list_add_tail((queue), (data))
#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)

void* queue_dequeue(Queue *queue);
void queue_destroy(Queue *queue, void (*destroy_data)(void *data));

#endif
