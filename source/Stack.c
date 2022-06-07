/******************************************************
*                   Stack.c
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
******************************************************/

#include <stdlib.h>

#include "LinkedList.h"
#include "Stack.h"

void* stack_pop(Stack *stack){
	void* data = stack_peek(stack);
	list_rem_head(stack);

	return data;
}

void stack_destroy(Stack *stack, void (*destroy_data)(void *data)){
	stack->destroy_data = destroy_data;
	list_destroy(stack);
}
