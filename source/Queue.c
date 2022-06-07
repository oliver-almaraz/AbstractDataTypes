/******************************************************
*                   Queue.c
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
******************************************************/

#include <stdlib.h>

#include "LinkedList.h"
#include "Queue.h"

void* queue_dequeue(Queue *queue){
	void *data = queue_peek(queue);
	list_rem_head(queue);

	return data;
}

void queue_destroy(Queue *queue, void (*destroy_data)(void *data)){
	queue->destroy_data = destroy_data;
	list_destroy(queue);
}
