/******************************************************
*                StackQueueExample.c
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************
*
*	Simple implementation example of both a STACK and a
*	QUEUE with the provided libraries.
*
*	In this example, the DATA contained by the nodes of
*	both DS (in this libraries, Queues and Stacks are
*	implemented on top of a Singly-Linked List) are
*	structs (Book) with three members each.
*
*	User-defined functions are created for dynamically
*	allocating DATA to be used with the DS, for freeing
*	such DATA at stack_destroy() and queue_destroy(),
*	and for displaying (printing) the contents of the DS.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"


// The STACK & QUEUE will hold Book structs as DATA
typedef struct {
	char *author;
	char *title;
	unsigned *pages;
} Book;


/***********************************
*       Function prototypes
***********************************/

// Allocates & initializes a Book struct
Book* createData(const char *author, const char *title, int pages);

// Frees dyn alloc mem from the Book struct and elmts
void destroyData(void *book);

// POPs the top elmt from STACK and ENQUEUEs it into
// a QUEUE
int readBook(Stack *stack, Queue *queue);

// Displays the contents of either a STACK or a QUEUE
void display(List *list);

// Very specific for this program:
// displays both the toRead stack and the finishedBooks queue.
void displayBoth(Stack *stack, Queue *queue);



/***********************************
*              main()
***********************************/

int main(){
	// Allocate and initialize Stack:
	Stack *toRead = stack_alloc();
	if (toRead == NULL)
		return -1;
	stack_init(toRead);

	// Allocate and initialize Queue:
	Queue *finishedBooks = queue_alloc();
	if (finishedBooks == NULL)
		return -1;
	queue_init(finishedBooks);

	// Allocate and init Book structs
	Book *Illiad = createData("Homer", "Illiad", 543);
	Book *Anabasis = createData("Xenophon", "Anabasis", 341);
	Book *Metamorphoses = createData("Ovid", "Metamorphoses", 807);
	Book *Faust = createData("Goethe", "Faust", 456);

	// Push BOOKS to toRead STACK
	// and check for NULL ptr
	Book *books[4] = {Illiad, Anabasis, Metamorphoses, Faust};
	for (int i=0; i<4; i++){
		if (books[i] == NULL)
			return -1;
		stack_push(toRead, books[i]);
	}

	displayBoth(toRead, finishedBooks);

	// Pop and enqueue Book once
	readBook(toRead, finishedBooks);
	printf("\n\n\nAfter reading one book:\n\n");
	displayBoth(toRead, finishedBooks);

	// Push new Book to Stack
	Book *Aeneid = createData("Virgil", "Aeneid", 1036);
	if (Aeneid == NULL)
		return -1;
	stack_push(toRead, Aeneid);
	printf("\n\nNew book pushed to toRead stack:\n\n");
	displayBoth(toRead, finishedBooks);

	// Pop and enqueue once again
	readBook(toRead, finishedBooks);
	printf("\n\n\nAfter reading a second book:\n\n");
	displayBoth(toRead, finishedBooks);

	stack_destroy(toRead, destroyData);
	queue_destroy(finishedBooks, destroyData);
}

/***********************************
*       Function definitions
***********************************/

Book* createData(const char *author, const char *title, int pages){
	Book *book = (Book*)malloc(sizeof(Book));
	if (book == NULL) return NULL;
	
	book->author = (char*)malloc(sizeof(strlen(author))+1);
	if (book->author == NULL) return NULL;
	strcpy(book->author, author);

	book->title = (char*)malloc(sizeof(strlen(title))+1);
	if (book->title == NULL) return NULL;
	strcpy(book->title, title);

	book->pages = (int*)malloc(sizeof(int));
	if (book->pages == NULL) return NULL;
	*(book->pages) = pages;

	return book;
}

void destroyData(void *book){
	// This function takes a void ptr as argument instead
	// of a Book ptr to make it compatible with the
	// second parameter of list_destroy()
	Book *bookptr = (Book*)book;
	free(bookptr->author);
	free(bookptr->title);
	free(bookptr->pages);
	free(book);
}

int readBook(Stack *stack, Queue *queue){
	Book *book = (Book*)stack_pop(stack);
	if (book == NULL)
		return -1;
	return queue_enqueue(queue, (void*)book);
}

void display(List *list){
	if (list->size == 0){
		printf("\n\t<is empty>\n");
		return;
	}

	Node *current = list->head;
	Book * book;

	while (current != NULL){
		// Casting from void* is necessary
		book = (Book*)current->data;
		printf("\n\tAuthor: %s\n", book->author);
		printf("\tTitle: %s\n", book->title);
		printf("\tPages: %d\n", *(book->pages));
		
		current = current->next;
	}
}

void displayBoth(Stack *stack, Queue *queue){
	printf("\n*Books to read (Stack):");
	display(stack);
	printf("\n*Finished books (Queue):");
	display(queue);
}