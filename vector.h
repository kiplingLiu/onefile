#ifndef VECTOR_GUARD
#define VECTOR_GUARD

struct vector {
	int len;	/* Current number of values */
	int max;	/* Allocated number of values */
	void **data;	/* Array of pointers to void */
};

struct vector *vector_init(void);
int vector_add(struct vector *v, void *datum);

#endif
