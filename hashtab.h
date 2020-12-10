#ifndef HASHTAB_GUARD
#define HASHTAB_GUARD

struct entry {
	char *key;
	void *data;
	struct entry *next;
};

typedef struct entry **hashtab;

hashtab *hashtab_init(int len);
struct entry *lookup(hashtab *ht, int len, char *key, int create, void *data);

#endif
