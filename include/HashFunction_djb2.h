/******************************************************
*               HashFunction_djb2.h
*	Created & mantained by: oliver.almaraz@gmail.com
*	for personal use. You may use and modify it.
*	github.com/oliver-almaraz/AbstractDataTypes
*******************************************************
*
*	Hash function written in 1991 by Daniel J.Bernstein
*	(djb) on 'comp.lang.c'. It's well suited for hash-
*	coding strings.
*
*	Notice that it returns an unsigned long, therefore
*	you should fit it into your desired table size.
*	The following "division method" accomplishes it:
*		int HashKey = (hash(<STRING>) % TABLE_SIZE);
*	It is suggested a TABLE_SIZE which is a prime
*	number not too close to a power of 2, while also
*	considering the load factor of each bucket. (Loudon, Kyle. 'Mastering Algorithms with C'. O'Reilly Media Inc., 1999).
*/

#ifndef HASH_FUNCTION_DJB2
#define HASH_FUNCTION_DJB2

unsigned long hash_djb2(void *str);

#endif
