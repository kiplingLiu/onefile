#include <stdlib.h>
#include <string.h>

enum { FALSE, TRUE };

void bubble_sort(int *a, int len);

void heapsort(int *a, int len);
void build_heap(int *a, int len);
void down_heap(int v, int *a, int len);

int merge_sort(int *a, int alen);
void merge(int *a, int alen, int *b, int blen, int *c, int clen);

void quicksort(int *a, int len);

void swap(int *a, int i, int j);

/* A collection of sorting algorithms */
int main(void)
{
	return 0;
}

void bubble_sort(int *a, int len)
{
	int left;	/* Number of elements left to sort */
	int swapped;	/* TRUE if there was a swap */
	int i;

	if (a == NULL)
		return;
	swapped = TRUE;
	for (left = len; left > 1 && swapped; left--) {
		swapped = FALSE;
		for (i = 0; i < left - 1; i++)
			if (a[i] > a[i + 1]) {
				swap(a, i, i + 1);
				swapped = TRUE;
			}
	}
}

void heapsort(int *a, int len)
{
	if (a == NULL)
		return;
	build_heap(a, len);
	while (len > 1) {
		swap(a, 0, len - 1);
		len--;
		down_heap(0, a, len);
	}
}

/* Build a heap from an arbitrarily labeled tree a */
void build_heap(int *a, int len)
{
	int v;

	if (a == NULL)
		return;
	for (v = len / 2 - 1; v >= 0; v--)
		down_heap(v, a, len);
}

/* Make a semi-heap rooted at a[v] into a heap */
void down_heap(int v, int *a, int len)
{
	if (a == NULL)
		return;
	while (v <= len / 2 - 1) {
		int w;	/* Index of child node to swap with node at a[v] */

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

	if (a == NULL || alen <= 1)
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

/* Merge b and c into a */
void merge(int *a, int alen, int *b, int blen, int *c, int clen)
{
	int i, j, k;

	if (a == NULL || b == NULL || c == NULL)
		return;
	j = k = 0;
	for (i = 0; i < alen; i++)
		if (j == blen)
			a[i] = c[k++];
		else if (k == clen)
			a[i] = b[j++];
		else if (b[j] < c[k])
			a[i] = b[j++];
		else
			a[i] = c[k++];
}

void quicksort(int *a, int len)
{
	int i, last;

	if (a == NULL || len <= 1)
		return;
	swap(a, 0, rand() % len);
	last = 0;
	for (i = 1; i < len; i++)
		if (a[i] < a[0])
			swap(a, ++last, i);
	swap(a, 0, last);
	quicksort(a, last);
	quicksort(a + last + 1, len - last - 1);
}

/* Swap a[i] and a[j] */
void swap(int *a, int i, int j)
{
	int tmp;

	if (a == NULL)
		return;
	tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}
