/******************************************************
*                   Stack.c
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
******************************************************/

#include <stdlib.h>

#include "LinkedList.h"
#include "Stack.h"

void stack_init(Stack *stack){
	list_init(stack, NULL);
}

int stack_push(Stack *stack,  void *data){
	return list_add_head(stack, data);
}

void* stack_pop(Stack *stack){
	Stack *data = stack_peek(stack);
	list_rem_head(stack);

	return data;
}

void stack_destroy(Stack *stack, void (*destroy_data)(void *data)){
	stack->destroy_data = destroy_data;
	list_destroy(stack);
}