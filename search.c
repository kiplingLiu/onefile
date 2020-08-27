#include <stdio.h>
#include <stdlib.h>

int sequential_search(int x, int *a, int len);
int binary_search(int x, int *a, int len);

/* A collection of searching algorithms */
int main(void)
{
	return 0;
}

int sequential_search(int x, int *a, int len)
{
	int i;

	for (i = 0; i < len; i++)
		if (a[i] == x)
			return i;
	return -1;
}

int binary_search(int x, int *a, int len)
{
	int low, high, mid;

	low = 0;
	high = len - 1;
	while (low <= high) {
		mid = low + (high - low) / 2;

		if (a[mid] == x)
			return mid;
		else if (a[mid] > x)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}
