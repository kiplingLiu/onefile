#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort(int *a, int len);

void heapsort(int *a, int len);
void build_heap(int *a, int len);
void down_heap(int v, int *a, int len);

int merge_sort(int *a, int alen);
void merge(int *a, int alen, int *b, int blen, int *c, int clen);

void swap(int *a, int i, int j);

/* A collection of sorting algorithms */
int main(void)
{
	return 0;
}

void bubble_sort(int *a, int len)
{
	int left;	/* Number of elements left to sort */
	int swapped;	/* 1 if there was a swap */
	int i;

	swapped = 1;
	for (left = len; left > 1 && swapped; left--) {
		swapped = 0;
		for (i = 0; i < left - 1; i++)
			if (a[i] > a[i + 1]) {
				swap(a, i, i + 1);
				swapped = 1;
			}
	}
}

void heapsort(int *a, int len)
{
	build_heap(a, len);

	while (len > 1) {
		swap(a, 0, len - 1);
		len--;
		down_heap(0, a, len);
	}
}

void build_heap(int *a, int len)
{
	for (int v = len / 2 - 1; v >= 0; v--)
		down_heap(v, a, len);
}

void down_heap(int v, int *a, int len)
{
	while (v <= len / 2 - 1) {
		int w;	/* Index of child node to swap with node at v */

		w = 2 * v + 1;
		if (w + 1 < len && a[w + 1] > a[w])
			w++;
		if (a[v] >= a[w])
			return;
		swap(a, v, w);
		v = w;
	}
}

int merge_sort(int *a, int alen)
{
	int *b, *c;
	int blen, clen;

	if (alen <= 1)
		return 0;

	blen = alen / 2;
	clen = alen - blen;
	if ((b = malloc(sizeof(int) * blen)) == NULL)
		return 1;
	if ((c = malloc(sizeof(int) * clen)) == NULL) {
		free(b);
		return 1;
	}
	memcpy(b, a, sizeof(int) * blen);
	memcpy(c, a + blen, sizeof(int) * clen);

	if (merge_sort(b, blen) == 1 || merge_sort(c, clen) == 1) {
		free(b);
		free(c);
		return 1;
	}

	merge(a, alen, b, blen, c, clen);

	free(b);
	free(c);

	return 0;
}

void merge(int *a, int alen, int *b, int blen, int *c, int clen)
{
	int i, j, k;

	j = k = 0;
	for (i = 0; i < alen; i++) {
		if (j == blen)
			a[i] = c[k++];
		else if (k == clen)
			a[i] = b[j++];
		else if (b[j] < c[k])
			a[i] = b[j++];
		else
			a[i] = c[k++];
	}
}

void swap(int *a, int i, int j)
{
	int tmp;

	tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}
