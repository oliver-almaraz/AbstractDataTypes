/******************************************************
*                   LinkedList.c
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
******************************************************/

#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

void list_init(List *list, void (*destroy_data)(void *data)){
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->destroy_data = destroy_data;
}

void list_destroy(List * list){
	while (list->size > 0)
		list_rem_head(list);
	// Clear memory
	memset(list, 0, sizeof(List));
	// Free memory allocated for List
	free(list);
}

int list_rem_next(List *list, Node *node){
	Node *old_node;

	// Do not remove from empty list
	if (list->size == 0)
		return -1;

	// Check for NULL ptr
	if (node == NULL)
		return -1;

	// Tail was passed, there isn't a next elmt
	if (node->next == NULL)
		return -1;

	// Remove element
	old_node = node->next; // Save pointer for free()
	node->next = node->next->next;

	// If tail was removed update new tail
	if (node->next == NULL)
		list->tail = node;
	
	// Call user defined fn to free node's data
	if (list->destroy_data != NULL)
		list->destroy_data(old_node->data);
	// Clear memory
	memset(old_node, 0, sizeof(Node));
	// Free memory allocated for node
	free(old_node);

	list->size--;
	return 0;
}

int list_rem_head(List *list){
	// Do not remove from empty list
	if (list->size == 0)
		return -1;

	// Backup ptr to node for free()
	Node *old_node = list->head;

	if (list->size == 1)
		// Head was the only node
		list->head = list->tail = NULL;
	else
		// Update new list's head
		list->head = list->head->next;

	// Destroy node's data;
	if (list->destroy_data != NULL)
		list->destroy_data(old_node->data);

	// Clear memory
	memset(old_node, 0, sizeof(Node));
	// Free() mem alocated for removed node
	free(old_node);
	list->size--;

	return 0;
}

int list_rem_tail(List *list){
	if (list->head->next == NULL)
		// Only one node in list
		list_rem_head(list);

	Node *current = list->head;

	while (current->next->next != NULL)
		// Find the node before the tail
		current = current->next;
	
	list_rem_next(list, current);

	return 0;
}

int list_add_head(List *list, void *data){
	if (list == NULL)
		return -1;

	Node *new_node = (Node*)calloc(1, sizeof(Node));	
	if (new_node == NULL)
		return -1;
	
	new_node->data = data;

	if (list->tail == NULL) {
		// If This is the first node added
		// it's also the tail
		list->tail = new_node;
		new_node->next = NULL;
	} else
		new_node->next = list->head;

	list->head = new_node;

	list->size++;
	return 0;
}

int list_add_tail(List *list, void *data){
	if (data == NULL || list == NULL)
		return -1;
	
	Node *node = (Node*)calloc(1, sizeof(Node));
	
	if (node == NULL)
		return -1;
	node->data = data;
	node->next = NULL;

	if (list->head == NULL){
		// If this is the first node added
		// it's also the head
		list->head = node;
	} else
		list->tail->next = node;

	list->tail = node;
	list->size++;
	return 0;
}
