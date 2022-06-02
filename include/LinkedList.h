/******************************************************
*					LinkedList.h
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************
*
*	Header file providing an interface for creating,
*	destroying, adding and removing elements from a
*	singly-linked lists whose STRUCTS are dynamically
*	allocated in the HEAP. Therefore, user should
*	check for a NULL pointer when calling:
*		List* alloc_list();
*
*	DATA contained by the NODES may be dyn. alloc.
*	In that case, it's the user's responsibility to:
*
*	- Allocate the DATA that will be passed to the
*		NODES at their creation.
*	- Create and pass a funtion to destroy such
*		dynamically allocated DATA once a node is
*		removed from the list.
*	- Call list_destroy() when the list is no
*		longer required to free() dyn. alloc. mem.
*
*	If the DATA is NOT dyn. allocated and/or there's
*	need to free() it after a NODE is destroyed,
*	pass NULL as the second argument to:
*		void list_init();
*
*	The user must NOT worry about:
*	- Allocating memory for the list's structs
*		(call alloc_list() instead).
*	- Freeing memory allocated for the structs if
*		list_destroy() or list_rem_*() are called.
*/



#ifndef S_LINKED_LIST_H
#define S_LINKED_LIST_H

#include <stdlib.h>
#include <string.h>

// Struct for the list's nodes
typedef struct _node {
	void *data;
	struct _node *next;
} Node;

// Struct for the list itself
typedef struct _list {
	Node *head;
	Node *tail;
	int size; // Number of elmts in list
	void (*destroy_data)(void *data);
	// The function to destroy the NODES' DATA is
	// passed as the second arg of list_init().
	// Creating that fn is the responsibility
	// of the user.
	// If NULL is passed to list_init(),
	// it is assumed that the user will either
	// pass NON dyn. alloc. data or that the user
	// will correctly handle allocated memory
	// later. 

} List;


/***********************************************
*				PUBLIC INTERFACE
***********************************************/

#define alloc_list() ((List*)malloc(sizeof(List)));

void list_init(List *list, void (*destroy_data)(void *data));
void list_destroy(List *list);
int list_rem_next(List *list, Node *node);
int list_rem_head(List *list);
int list_rem_tail(List *list);
int list_add_head(List *list, void *data);
int list_add_tail(List *list, void *data);

#endif
