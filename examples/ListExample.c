/******************************************************
*					ListExample.c
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************
*
*	Simple example of implementation of the singly-linked
*	list using the provided library.
*	In this example, the DATA (strings) passed to the list
*	is copied from a global array (ingredienti[]) to the
*	HEAP calling createData(), which returns a void ptr
*	to the dyn. allocated string.
*	Because this implementation uses dynamically allocated
*	DATA, a custom destroyData() function has to be passed
*	as the second argument to list_init() to free() DATA
*	every time user calls list_rem_*() or list_destroy().
*
*	Function printList() displays the strings contained
*	in the list (list->node->data).
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "LinkedList.h"

void destroyData(void* data);
void* createData(const char* string);
void printList(List* list);

const char *ingredienti[6] = {
	"Guanciale", "Pecorino", "Pepe", "Spaghetti",
	"Uova", "Sale"
};

int main(){
    List *Carbonara = alloc_list();
	if (Carbonara == NULL)
		return -1;
    list_init(Carbonara, destroyData);

	for (int i=0; i<6; i++)
		list_add_head(Carbonara, (createData(ingredienti[i])));

	printf("All elements added to HEAD:\n");
    printList(Carbonara);

	list_rem_head(Carbonara);
	printf("\nHead removed:\n");
	printList(Carbonara);

	list_rem_tail(Carbonara);
	printf("\nTail removed:\n");
	printList(Carbonara);

	list_add_tail(Carbonara, (createData(ingredienti[0])));
	printf("\nTail added once again:\n");
	printList(Carbonara);

	list_rem_next(Carbonara, Carbonara->head);
	printf("\nNode next to HEAD removed:\n");
	printList(Carbonara);

	list_destroy(Carbonara);

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

void printList(List* list){
	// Nothing to print from empty list
    if (list->size == 0)
        return;

    Node *current = list->head;
	while (current != NULL){
        printf("%s\n", current->data);
        current = current->next;
	}
}
