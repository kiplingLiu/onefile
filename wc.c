#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

enum { FALSE, TRUE };

int count_lwc(FILE *fp, int *nlp, int *nwp, int *ncp);
void print_lwc(int nl, int nw, int nc, char *fn);

int lf, wf, cf;		/* lf is TRUE if the -l option was specified, etc. */

/* Count lines, words, and characters in files */
int main(int argc, char **argv)
{
	int i;		/* Index into argv */
	int opt;	/* TRUE if at least one option was specified */

	int c;		/* Number of operands */
	int tl, tw, tc;	/* Total line, word, and character counts */
	
	/* Parse arguments */
	opt = FALSE;
	for (i = 1; i < argc && *argv[i] == '-'; i++) {
		if (strcmp(argv[i], "-") == 0)
			break;
		if (strcmp(argv[i], "--") == 0) {
			i++;
			break;
		}
		opt = TRUE;
		while (*++argv[i])
			switch (*argv[i]) {
			case 'l':
				lf = TRUE;
				break;
			case 'w':
				wf = TRUE;
				break;
			case 'c':
				cf = TRUE;
				break;
			default:
				fprintf(stderr, "wc: illegal option %c\n",
					*argv[i]);
				return 1;
			}
	}
	if (opt == FALSE)
		lf = wf = cf = TRUE;

	if (i == argc) {
		if (count_lwc(stdin, &tl, &tw, &tc) == 1)
			goto err_count_lwc;
		print_lwc(tl, tw, tc, "");
	} else {
		c = 0;
		tl = tw = tc = 0;
		for (; i < argc; i++) {
			FILE *fp;
			int nl, nw, nc;

			if (strcmp(argv[i], "-") == 0) {
				if (count_lwc(stdin, &nl, &nw, &nc) == 1)
					goto err_count_lwc;
			} else if ((fp = fopen(argv[i], "r")) == NULL) {
				fprintf(stderr, "wc: can't open file %s\n",
					argv[i]);
				return 1;
			} else {
				if (count_lwc(fp, &nl, &nw, &nc) == 1)
					goto err_count_lwc;
				if (fclose(fp) == EOF) {
					fprintf(stderr,
						"wc: can't close file %s\n",
						argv[i]);
					return 1;
				}
			}
			print_lwc(nl, nw, nc, argv[i]);
			if (tl > INT_MAX - nl || tw > INT_MAX - nw ||
			    tc > INT_MAX - nc) {
				fprintf(stderr, "wc: integer overflow\n");
				return 1;
			}
			tl += nl;
			tw += nw;
			tc += nc;
			c++;
		}
		if (c > 1)
			print_lwc(tl, tw, tc, "total");
	}

	if (ferror(stdout)) {
		fprintf(stderr, "wc: error writing stdout\n");
		return 2;
	}

	return 0;

err_count_lwc:
	fprintf(stderr, "wc: error counting\n");
	return 1;
}

/*
 * Count the number of lines, words, and characters in fp; store the results
 * in nlp, nwp, and ncp, respectively. Return 0, or 1 on error.
 */
int count_lwc(FILE *fp, int *nlp, int *nwp, int *ncp)
{
	int in;
	int c;

	if (fp == NULL || nlp == NULL || nwp == NULL || ncp == NULL)
		return 1;
	*ncp = *nlp = *nwp = 0;
	in = FALSE;
	while ((c = getc(fp)) != EOF) {
		if (*ncp > INT_MAX - 1)	
			return 1;
		(*ncp)++;
		if (c == '\n') {
			if (*nlp > INT_MAX - 1)
				return 1;
			(*nlp)++;
		}
		if (!isspace(c) && !in) {
			if (*nwp > INT_MAX - 1)
				return 1;
			in = TRUE;
			(*nwp)++;
		} else if (isspace(c) && in)
			in = FALSE;
	}

	return 0;
}

/*
 * Print nl, nw, and/or nc depending on lf, wf, and cf, respectively. Errors on
 * stdout are *not* reported.
 */
void print_lwc(int nl, int nw, int nc, char *fn)
{
	if (lf)
		printf("%d", nl);
	printf(" ");
	if (wf)
		printf("%d", nw);
	printf(" ");
	if (cf)
		printf("%d", nc);
	if (fn != NULL)
		printf("%s%s\n", fn[0] == '\0' ? "" : " ", fn);
}
