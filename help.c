#include <ctype.h>
#include <stdio.h>

#include "help.h"

#ifdef HELP_TEST
int main(void)
{
	return 0;
}
#endif

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
