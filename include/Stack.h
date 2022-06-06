/******************************************************
*                    Stack.h
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************
*
*	C library providing an interface for creating and
*	destroying STACKS, as well as pushing, popping
*	and peeking elements from them.
*
*	This library is an EXTENSION of the LinkedList
*	lib provided in this repository. Therefore, you
*	should be aware of the description presented in
*	./LinkedList.h. For even more detail, you may look
*	into ./source/LinkedList.c.
*
*	Stack_init(stack) calls list_init(stack, NULL).
*	Passing NULL instead of a destroy_data() fn allows
*	the user to use the data stored in the element last
*	popped: stack_pop() returns a pointer to it.
*******************************************************
*	As a consecuence, the user is ALWAYS responsible
*	for freeing dyn. alloc. data after stack_pop() is
*	called.
*******************************************************
*
*	In the other hand, stack_destroy(), takes as its
*	second argument a function ptr to free the DATA in
*	case it was dyn. alloc. when removing all the elmts
*	in the stack. As with list_init(), you may pass
*	NULL if DATA is not dyn. alloc.
*
*	Finally, stack_peek() returns a ptr to the data of
*	the element at the top of the stack without
*	popping it.
*******************************************************
*   You should always check for a NULL pointer
*   when calling stack_peek() and stack_pop();
******************************************************/

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "LinkedList.h"

typedef List Stack;

/***********************************************
*               PUBLIC INTERFACE
***********************************************/

#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)

void stack_init(Stack *stack);
int stack_push(Stack *stack,  void *data);
void* stack_pop(Stack *stack);
void stack_destroy(Stack *stack, void (*destroy_data)(void *data));

#endif