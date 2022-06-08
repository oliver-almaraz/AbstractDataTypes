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

unsigned long hash(unsigned char *str){
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c;	
	return hash;
}
