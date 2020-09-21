#include <stdio.h>

/* Output the first 100 FizzBuzz numbers */
int main(void)
{
	int i;

	for (i = 1; i < 100; i++) {
		if (i % 3 == 0 && i % 5 == 0)
			printf("FizzBuzz");
		else if (i % 3 == 0)
			printf("Fizz");
		else if (i % 5 == 0)
			printf("Buzz");
		else
			printf("%d", i);
		printf("\n");
	}

	if (ferror(stdout)) {
		fprintf(stderr, "fizzbuzz: error writing stdout\n");
		return 2;
	}

	return 0;
}
