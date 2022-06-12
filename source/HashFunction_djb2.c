/******************************************************
*               HashFunction_djb2.c
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************
*
*	Hash function well suited for strings written by
*	Daniel J. Bernstein.
*/

// Read Header file:
#include "HashFunction_djb2.h"

unsigned long hash_djb2(void *str){
	unsigned long hash = 5381;
	int c;
	unsigned char *string = (unsigned char*)str;

	while (c = *string++)
		hash = ((hash << 5) + hash) + c;	
	return hash;
}
