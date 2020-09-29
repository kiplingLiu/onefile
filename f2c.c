#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN 10

char *fgetw(char *word, int len, FILE *fp);

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

/*
 * Read at most len - 1 continuous non-whitespace characters from fp into word.
 * Return word, or NULL on end of file or error.
 */
char *fgetw(char *word, int len, FILE *fp)
{
	int c;
	char *w;

	if (word == NULL || len < 1 || fp == NULL)
		return NULL;
	w = word;
	while (isspace(c = fgetc(fp)))
		;
	if (c == EOF)
		return NULL;
	while (c != EOF && !isspace(c) && --len > 0) {
		*w++ = c;
		c = fgetc(fp);
	}
	if (c != EOF)
		if (ungetc(c, fp) == EOF)
			return NULL;
	*w = '\0';
	if (len <= 0)
		return NULL;

	return word;
}
