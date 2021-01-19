#include <stdlib.h>

#include "bintree.h"

#ifdef BINTREE_TEST
int main(void)
{
	return 0;
}
#endif

/*
 * Return a pointer to a a node of a binary tree (aka bintree) with label label
 * and left and right children initialized to NULL, or NULL if the allocation
 * fails.
 *
 * Binary trees should always be initialized using this function before any
 * other operations are performed.
 */
struct bintree *bintree_init(void *label)
{
	struct bintree *bt;

	if ((bt = malloc(sizeof(struct bintree))) == NULL)
		return NULL;
	bt->label = label;
	bt->left = NULL;
	bt->right = NULL;

	return bt;
}

/*
 * Add a new child to bt (or replace an existing one). If which equals 1, add a
 * right child; otherwise, add a left child. Return the child, or NULL on
 * error.
 */
struct bintree *bintree_add(struct bintree *bt, int which, void *label)
{
	struct bintree **child;

	if (bt == NULL)
		return NULL;
	child = which ? &(bt->right) : &(bt->left);
	if ((*child = bintree_init(label)) == NULL)
		return NULL;

	return *child;
}

/* See [LeetCode 226](https://leetcode.com/problems/invert-binary-tree/). */
void bintree_invert(struct bintree *bt)
{
	struct bintree *tmp;

	if (bt == NULL)
		return;
	bintree_invert(bt->left);
	bintree_invert(bt->right);
	tmp = bt->left;
	bt->left = bt->right;
	bt->right = tmp;
}
