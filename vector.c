#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct vector {
	int len;	/* Current number of values */
	int max;	/* Allocated number of values */
	void **data;	/* Array of pointers to void */
};

enum { VINIT = 1, VGROW = 2 };

struct vector *vector_init(void);
int vector_add(struct vector *v, void *datum);

int main(void)
{
	return 0;
}

/*
 * Return a pointer to an empty vector with space allocated for VINIT elements
 * or NULL if the allocation fails.
 *
 * Vectors should always be initialized using this function before any
 * other operations are performed.
 */
struct vector *vector_init(void)
{
	struct vector *v;

	if ((v = malloc(sizeof(struct vector))) == NULL)
		return NULL;
	if ((v->data = malloc(VINIT * sizeof(void *))) == NULL) {
		free(v);
		return NULL;
	}
	v->len = 0;
	v->max = VINIT;

	return v;
}

/*
 * Add datum to the end of v->data. If there is not enough space, grow v->data
 * by a factor of VGROW. Return the index of datum, or -1 on error.
 */
int vector_add(struct vector *v, void *datum)
{
	void *vp;

	if (v == NULL)
		return -1;
	if (v->len >= v->max) {
		if (v->max > INT_MAX / VGROW ||
		    v->max * VGROW > SIZE_MAX / sizeof(void *))
			return -1;
		vp = realloc(v->data, VGROW * v->max * sizeof(void *));
		if (vp == NULL)
			return -1;
		v->max *= VGROW;
		v->data = vp;
	}
	v->data[v->len] = datum;

	return v->len++;
}
