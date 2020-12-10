#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hashtab.h"

unsigned hash(char *key, int len);

#ifdef HASHTAB_TEST
int main(void)
{
	return 0;
}
#endif

/*
 * Return a pointer to an array of struct entry (aka hashtab) with length len or
 * NULL if the allocation fails. Every element of the array is initialized to
 * NULL.
 *
 * Hash tables should always be initialized using this function before any
 * other operations are performed.
 */
hashtab *hashtab_init(int len)
{
	hashtab *ht;
	int i;

	if (len < 1)
		return NULL;
	if ((ht = malloc(sizeof(hashtab))) == NULL)
		return NULL;
	if (len > SIZE_MAX / sizeof(struct entry *) ||
	    (*ht = malloc(len * sizeof(struct entry *))) == NULL) {
		free(ht);
		return NULL;
	}
	for (i = 0; i < len; i++)
		(*ht)[i] = NULL;

	return ht;
}

/*
 * Look for a struct entry in *ht whose key is equal to the key parameter
 * (by string comparison). If such a struct entry is found, return a pointer to
 * it. Otherwise, if create is nonzero, allocate memory for a new struct entry
 * (returning NULL if the allocation fails), use key and data to initialize its
 * members, insert it into *ht, and return a pointer to it. Finally, if create
 * is zero, return NULL.
 */
struct entry *lookup(hashtab *ht, int len, char *key, int create, void *data)
{
	int v;
	struct entry *e;

	v = hash(key, len);
	for (e = (*ht)[v]; e != NULL; e = e->next)
		if (strcmp(key, e->key) == 0)
			return e;
	if (create) {
		if ((e = malloc(sizeof(struct entry))) == NULL)
			return NULL;
		e->key = key;
		e->data = data;
		e->next = (*ht)[v];
		(*ht)[v] = e;
	}

	return e;
}

unsigned hash(char *key, int len)
{
	unsigned v;
	unsigned char *p;

	v = 0;
	for (p = (unsigned char *) key; *p != '\0'; p++)
		v = 31 * v + *p;

	return v % len;
}
