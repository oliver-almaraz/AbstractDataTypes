/******************************************************
*                   DoublyLinkedList.c
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
******************************************************/

#include <stdlib.h>
#include <string.h>

#include "DoublyLinkedList.h"

void dlist_init(DList *list, void (*destroy_data)(void *data)){
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->destroy_data = destroy_data;
}

int dlist_rem(DList *list, DNode *node){
    // Do not remove from empty list or NULL ptr passed
    if (node == NULL || list->size == 0)
        return -1;

    // Node passed is HEAD
    if (node == list->head){
        // Node passed was the only elmt in list
        if (list->size == 1)
            list->head = list->tail = NULL;
        else {
            list->head = list->head->next;
            list->head->prev = NULL;
        }
    }
    // Node passed is TAIL
    else if (node == list->tail){
        if (list->size == 1)
            list->head = list->tail = NULL;
        else {
            list->tail = list->tail->prev;
            list->tail->next = NULL;
        }
    }
    // Node passed is neither HEAD nor TAIL and there
    // are at least 3 elmts in list
    else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    memset(node, 0, sizeof(DNode));
    free(node);
    list->size--;

    return 0;
}

void dlist_destroy(DList *list){
    while (list->size > 0)
        dlist_rem(list, list->head);
    memset(list, 0, sizeof(DList));
	// Free memory allocated for List
	free(list);
}

int dlist_ins_next(DList *list, DNode *node, void *data){
    // Only accept a NULL node when list is empty
    if (node == NULL && list->size > 0)
        return -1;

    DNode *new_node = (DNode*)calloc(1, sizeof(DNode));
    if (new_node == NULL)
        return -1;
    new_node->data = data;

    if (list->size == 0){
        // Adding first elmt to the list
        new_node->prev = new_node->next = NULL;
        list->head = list->tail = new_node;
    } else {
        new_node->next = node->next;
        new_node->prev = node;

        if (node->next == NULL)
            // new_node is now TAIL
            list->tail = new_node;
        else
            // There's a NODE after new_node, update NEXT
            node->next->prev = new_node;

        node->next = new_node;
    }
     list->size++;
     return 0;

}

int dlist_ins_prev(DList *list, DNode *node, void *data){
    // Only accept a NULL node when list is empty
    if (node == NULL && list->size > 0)
        return -1;

    DNode *new_node = (DNode*)calloc(1, sizeof(DNode));
    if (new_node == NULL)
        return -1;
    new_node->data = data;

    if (list->size == 0){
        // Adding first elmt to the list
        new_node->prev = new_node->next = NULL;
        list->head = list->tail = new_node;
    } else {
        new_node->next = node;
        new_node->prev = node->prev;

        if (node->prev == NULL)
            // new_node is now HEAD
            list->head = new_node;
        else
            // There's a NODE before, update NEXT 
            node->prev->next = new_node;

        node->prev = new_node;
    }
    list->size++;
    return 0;
}