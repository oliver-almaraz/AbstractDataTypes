/******************************************************
*                 CHTableExample.c
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************
*
*	Simple implementation example of a Chained Hash
*	Table.
*
*	In this example, the elements stored in the TABLE
*	are structs (Books) with tree members each.
*
*	User-defined functions are created for dynamically
*	allocating DATA for the Books and for freeing
*	such DATA at chtable_destroy().
*	I took borrowed a very nice HASH function (see .h)
*	A trivial MATCH function is also created for demo.
*	Finally, a displayTable() fn shows the contents of
*	the table and how they are distributed.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "LinkedList.h"
#include "HashFunction_djb2.h"
#include "ChainedHashTable.h"

#define TRUE 1
#define FALSE 0

// This Hash Table will contain books
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

// Returns a non-zero value if both structs match
int match(void *struct1, void *struct2);

// Display all the buckets in Table and the elmts in them
void displayTable(ChainedHashTable* table);

/***********************************
*             main()
***********************************/

int main(){
	ChainedHashTable *biblio = chtable_alloc();
	if (biblio == NULL)
		return -1;
	chtable_init(biblio, 7, hash_djb2, match, destroyData);

	// Allocate and init Book structs
	Book *Illiad = createData("Homer", "Illiad", 543);
	Book *Anabasis = createData("Xenophon", "Anabasis", 341);
	Book *Metamorphoses = createData("Ovid", "Metamorphoses", 807);
	Book *Faust = createData("Goethe", "Faust", 456);
	Book *Ponticae = createData("Ovid", "Ponticae", 312);
	Book *Orestes = createData("Sophocles", "Orestes", 74);
	Book *Heracles = createData("Seneca", "Heracles Mainomenos", 93);
	Book *Heauton = createData("Terence", "Heauton Timoroumenos", 84);
	Book *Asinus = createData("Apuleius", "Asinus aureus", 547);

	// Insert Books into TABLE
	Book *books[9] = {
		Illiad, Anabasis, Metamorphoses, Faust, Ponticae, Orestes,
		Heracles, Heauton, Asinus
	};
	for (int i=0; i<9; i++){
		if (books[i] == NULL)
			return -1;
		chtable_insert(biblio, books[i]);
	}

	printf("\nThere are %d  buckets for a total of 9 elements,\n", biblio->buckets);
	printf("This is how the elements are distributed in the buckets:\n");
	displayTable(biblio);

	printf("\nLooking for book 'Illiad' in TABLE...\n");
	Book *foundBook = chtable_lookup(biblio, Illiad);
	if (foundBook != NULL)
		printf("Book found! Author is: '%s'\n", foundBook->author);

	printf("\nRemoving 'Faust' from TABLE...\n");
	chtable_remove(biblio, Faust);
	printf("'Faust' removed!\n");

	// Faust is not a valid pointer anymore
	// Create that book again:
	Faust = createData("Goethe", "Faust", 456);

	// Search for it again in TABLE
	printf("\nLooking for 'Faust' in TABLE...\n");
	foundBook = chtable_lookup(biblio, Faust);
	if (foundBook == NULL)
		printf("'Faust' no longer found in TABLE.\n");

	chtable_destroy(biblio);
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

int match(void *struct1, void *struct2){
	if (struct1 == NULL || struct2 == NULL)
		return FALSE;

	Book *book1 = (Book*)struct1;
	Book *book2 = (Book*)struct2;

	return ((strcmp(book1->title, book2->title) == 0) ? TRUE : FALSE);
}

void displayTable(ChainedHashTable* ch_table){
	// For every bucket
	for (int i=0; i<ch_table->buckets; i++){
		printf("table[%d]:\n", i);
		List *bucketList = &ch_table->table[i];
		// For every elmt in that bucket
		for (
			// Start at the HEAD of the bucket:
			Node *element =  bucketList->head;
			// Until the tail is reached
			element != NULL;
			element = element->next
		){
			Book *book = (Book*)element->data;
			printf("\t%s\n", book->title);
		}
	}
}
