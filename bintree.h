#ifndef BINTREE_GUARD
#define BINTREE_GUARD

struct bintree {
	void *label;
	struct bintree *left, *right;
};

struct bintree *bintree_init(void *label);
struct bintree *bintree_add(struct bintree *bt, int which, void *label);
void bintree_invert(struct bintree *bt);

#endif
