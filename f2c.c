#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "help.h"

enum { LEN = 10 };

/* Convert Fahrenheit to Celsius */
int main(void)
{
	char buf[LEN];

	while (fgetw(buf, LEN, stdin) != NULL) {
		double f;

		f = atof(buf);
		if (errno == ERANGE) {
			fprintf(stderr,
				"f2c: floating point overflow or underflow\n");
			return 1;
		}
		printf("%g\n", 5.0 / 9 * (f - 32));
	}

	if (ferror(stdout)) {
		fprintf(stderr, "f2c: error writing stdout\n");
		return 2;
	}

	return 0;
}
