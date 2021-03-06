/******************************************************
*               DoublyLinkedList.h
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************
*
*	C library providing an interface for creating,
*	destroying, adding and removing elements from
*	doubly-linked lists whose STRUCTS are dynamically
*	allocated in the HEAP. Therefore, user should
*	check for a NULL pointer when calling:
*		dlist_alloc();
*
*	DATA contained by the NODES may be dyn. alloc.
*	In that case, it's the user's responsibility to:
*
*	- Allocate the DATA that will be passed to the
*		NODES at their creation.
*	- Create and pass a funtion to destroy such
*		dynamically allocated DATA once a node is
*		removed from the list.
*	- Call dlist_destroy() when the list is no
*		longer required to free() dyn. alloc. mem.
*
*	If the DATA is NOT dyn. allocated and/or there's
*	need to free() it after a NODE is destroyed,
*	pass NULL as the second argument to:
*		void dlist_init();
*
*	The user must NOT worry about:
*	- Allocating memory for the list's structs
*		(call dlist_alloc() instead).
*	- Freeing memory allocated for the structs if
*		dlist_destroy() or dlist_rem() are called.
*/

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdlib.h>
#include <string.h>

//Struct fot the list's nodes
typedef struct _DNode {
	void *data;
	struct _DNode *next;
	struct _DNode *prev;
} DNode;

// Struct for the list itself
typedef struct _DList {
	DNode *head;
	DNode *tail;
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

} DList;

/***********************************************
*              PUBLIC INTERFACE
***********************************************/

#define dlist_alloc() ((DList*)malloc(sizeof(DList)));

void dlist_init(DList *list, void (*destroy_data)(void *data));
int dlist_rem(DList *list, DNode *node);
void dlist_destroy(DList *list);
int dlist_ins_next(DList *list, DNode *node, void *data);
int dlist_ins_prev(DList *list, DNode *node, void *data);

#endif
