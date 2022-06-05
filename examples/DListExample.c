/******************************************************
*                   DListExample.c
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************
*
*	Simple example of implementation of A DOUBLY-linked
*	list using the provided library.
*	In this example, the DATA (strings) passed to the list
*	is copied from a global array (ingredienti[]) to the
*	HEAP calling createData(), which returns a ptr to the
*	dyn. allocated string.
*	Because this implementation uses dynamically allocated
*	DATA, a custom destroyData() function has to be passed
*	as the second argument to list_init() to free() DATA
*	every time user calls list_rem() or list_destroy().
*
*	Function printList() displays the strings contained
*	in the list (list->node->data).
*
*	Function findNode() returns a pointer to the NODE of
*	the LIST that contains the STRING passed as the second
*	parameter. It returns NULL if STRING was not found.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "DoublyLinkedList.h"

void destroyData(void* data);
void* createData(const char *string);
void printList(DList *list);
DNode* findNode(DList *list, const char *string);

const char *ingredienti[4] = {
	"Patate", "Farina", "Semola",
	"Uova"
};

int main(){
	DList *Gnocchi = alloc_dlist();
	if (Gnocchi == NULL)
		return -1;
	dlist_init(Gnocchi, destroyData);

	for (int i=0; i<4; i++)
		dlist_ins_next(Gnocchi, Gnocchi->tail, createData(ingredienti[i]));

	printf("All the elements added to the list:\n");
	printList(Gnocchi);

	printf("\nThe node before 'Semola':\n");
	DNode *semola = findNode(Gnocchi, "Semola");
	printf(semola->prev->data);

	printf("\n\nInsert 'Sale' before 'Semola':\n");
	dlist_ins_prev(Gnocchi, semola, createData("Sale"));
	printList(Gnocchi);

	dlist_destroy(Gnocchi);
}

void destroyData(void* data){
	memset(data, 0, sizeof(data));
	free(data);
}

void* createData(const char* string){
	char *data = (char*)malloc(strlen(string)+sizeof('\0'));
	strcpy(data, string);
	return (void*)data;
}

void printList(DList* list){
	// Nothing to print from empty list
	if (list->size == 0)
		return;

	DNode *current = list->head;
	while (current != NULL){
		printf("%s\n", current->data);
		current = current->next;
	}
}

DNode* findNode(DList *list, const char *string){
	DNode *current = list->head;
	while (current != NULL){
		if (strcmp(current->data, string) == 0)
			return current;
		else
			current = current->next;
	}
	return NULL;
}