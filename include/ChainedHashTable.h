/******************************************************
*                ChainedHashTable.h
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************
*
*	C library providing an interface for creating and
*	destroying a Chained Hash Table, as well as for
*	inserting, removing and searching elements in it.
*
*	This library is an EXTENSION of the LinkedList
*	lib provided in this repository. Therefore, you
*	should be aware of the description presented in
*	./LinkedList.h. For even more detail, you may look
*	into ./source/LinkedList.c.
*
*	chtable_alloc() allocates space for the structure
*	of the data structure which is freed when calling
*	chtable_destroy().
*
*	chtable_init() takes a destroy_data() function
*	that will be passed to every bucket for freeing
*	the memory allocated for every Linked List.
*
*	chtable_lookup() calls the MATCH function passed
*	to chtable_init() to compare its second argument
*	with the elements in the TABLE. If the element is
*	found, chtable_lookup returns a pointer to the
*	DATA element of the node (list->node->data).
*
********************************************************
*	chtable_remove() DESTROYS the element passed to it
*	and frees the allocated mem for it. You cannot
*	access a table element after you passed it to
*	chtable_remove()!
********************************************************
*
*	User has to choose appropriate functions:
*	(examples are provided in this repository)
*		int hash_fn(void *key)
*		int match(void *key1, void *key2)
*		void destroy(void *data)
*	Also, user must decide a suitable number of
*	buckets (see ./HashFunction_djb2.h for suggestions)
*/

#ifndef CHAINED_HASH_TABLE
#define CHAINED_HASH_TABLE

#include <stdlib.h>
#include "LinkedList.h"

// Structure  for the Chained Hash TABLE
typedef struct ChainedHashTable_ {
	List *table; // The array of buckets

	int buckets; // Number of buckets (L. Lists) in TABLE
	int size; // Number of elements

	// Hash function
	long unsigned int (*hash_fn)(void *key);
	// Match function
	int (*match)(void *key1, void *key2);

	// Destroy function
	// It's the destroy_data function that will be
	// passed to each bucket (L. List) to destroy the
	// NODE's DATA. (See LinkedList.h)
	void (*destroy_data)(void *data);
} ChainedHashTable;

/***********************************************
*               PUBLIC INTERFACE
***********************************************/

#define chtable_alloc() (ChainedHashTable*)malloc(sizeof(ChainedHashTable))

int chtable_init(
	ChainedHashTable *ch_table, int buckets,
	long unsigned int (*hash_fn)(void *key),
	int (*match)(void *key1, void *key2),
	void (*destroy)(void *data)
);

void* chtable_lookup(ChainedHashTable *ch_table, void *data);
int chtable_insert(ChainedHashTable *ch_table, void *data);
int chtable_remove(ChainedHashTable *ch_table, void *data);
void chtable_destroy(ChainedHashTable *ch_table);

#endif
