#include <stdio.h>

/* Print hello, world */
int main(void)
{
	printf("hello, world\n");

	if (ferror(stdout)) {
		fprintf(stderr, "hello: error writing stdout\n");
		return 2;
	}

	return 0;
}
