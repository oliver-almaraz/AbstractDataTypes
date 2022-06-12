/******************************************************
*                ChainedHashTable.c
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************/

#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "ChainedHashTable.h"

int chtable_init (
	ChainedHashTable *ch_table, int buckets,
	long unsigned int (*hash_fn)(void *key),
	int (*match)( void *key1, void *key2),
	void (*destroy_data)(void *data)
)
{
	// Allocate contiguous memory for the table
	// (array of linked lists)
	ch_table->table = (List*)malloc(buckets * sizeof(List));
	if (ch_table->table == NULL) return -1;

	// Number of buckets in table
	ch_table->buckets = buckets;

	// Initialize the buckets in table
	for (int i=0; i < buckets; i++){
		// We can perform pointer arithmetic because
		// we allocated contiguous mem for _table_
		List *bucket = ch_table->table + i;
		list_init(bucket, destroy_data);
	}

	ch_table->hash_fn = hash_fn;
	ch_table->match = match;
	ch_table->destroy_data = destroy_data;

	ch_table->size = 0;

	return 0;
}

void* chtable_lookup(ChainedHashTable *ch_table, void *data){
	// Calculate to what bucket DATA belongs
	int bucket = ch_table->hash_fn(data) % ch_table->buckets;
	// Get a pointer to that bucket
	// ("&" is required because array[] notation dereferences)
	List *bucketList = &ch_table->table[bucket];

	for (
		// Start at the HEAD of the bucket:
		Node *element =  bucketList->head;
		// Until the tail is reached
		element != NULL;
		element = element->next
	)
	{
		if (ch_table->match(data, element->data)){
			// Element found, return ptr to data
			return element->data;
		}
	}
	// Not found
	return NULL;
}

int chtable_insert(ChainedHashTable *ch_table, void *data){
	// Check if DATA is already in the table
	if (chtable_lookup(ch_table, data) != NULL)
		return 1;

	int bucket =  ch_table->hash_fn(data) % ch_table->buckets;

	int retval = list_add_head(&ch_table->table[bucket], data);
	if (retval == 0)
		ch_table->size++;

	// retuns -1 if it could not allocate the elmt
	return retval;
}

int chtable_remove(ChainedHashTable *ch_table, void *data){
	// Calculate to what bucket DATA belongs
	int bucket = ch_table->hash_fn(data) % ch_table->buckets;

	// Get a pointer to that bucket
	// ("&" is required because array[] notation dereferences)
	List *bucketList = &ch_table->table[bucket];

	// If the node to remove is not at the HEAD,
	// we'll list_rem_next using this prev ptr.
	Node *prev;

	for (
		// Start at the HEAD of the bucket:
		Node *element =  bucketList->head;
		// Until the tail is reached
		element != NULL;
		element = element->next
	)
	{
		if (ch_table->match(data, element->data)){
			// Element found, remove it

			// Check if it's the list's HEAD
			if (element == bucketList->head){
				int retval = list_rem_head(bucketList);
				if (retval == 0){
					ch_table->size--;
					return 0;
				}
			} else {
				// Element it elsewhere in the list
				int retval = list_rem_next(bucketList, prev);
				if (retval == 0){
					ch_table->size--;
					return 0;
				}
			}
		} else
		// Save this ptr for list_rem_next if the
		// elmt is found in the next iteration
		prev = element;
	}
	// Loop ended, element not found
	return -1;
}

void chtable_destroy(ChainedHashTable *ch_table){
	// We cannot use list_destroy() here because that
	// fn assumes that we allocated each list individually
	// with list_alloc(), and we didn't.
	for (int i=0; i < ch_table->buckets; i++){
		List *bucket = &ch_table->table[i];
		while (bucket->size > 0)
		    list_rem_head(bucket);
		// Clear
		memset(bucket, 0, sizeof(List));
	}
	// Mem for the buckets was allocated contigu.
	// and is now freed as a single pointer
	free(ch_table->table);
	memset(ch_table, 0, sizeof(ChainedHashTable));
	free(ch_table);
}
