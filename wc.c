#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum { FALSE, TRUE };

void count_lwc(FILE *fp, int *nlp, int *nwp, int *ncp);
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
		count_lwc(stdin, &tl, &tw, &tc);
		print_lwc(tl, tw, tc, "");
	} else {
		c = 0;
		tl = tw = tc = 0;
		for (; i < argc; i++) {
			FILE *fp;
			int nl, nw, nc;

			if (strcmp(argv[i], "-") == 0)
				count_lwc(stdin, &nl, &nw, &nc);
			else if ((fp = fopen(argv[i], "r")) == NULL) {
				fprintf(stderr, "wc: can't open file %s\n",
					argv[i]);
				return 1;
			} else {
				count_lwc(fp, &nl, &nw, &nc);
				if (fclose(fp) == EOF) {
					fprintf(stderr,
						"wc: can't close file %s\n",
						argv[i]);
					return 1;
				}
			}
			print_lwc(nl, nw, nc, argv[i]);
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
}

/*
 * Count the number of lines, words, and characters in fp; store the results
 * in nlp, nwp, and ncp, respectively
 */
void count_lwc(FILE *fp, int *nlp, int *nwp, int *ncp)
{
	int in;
	int c;

	*ncp = *nlp = *nwp = 0;
	in = FALSE;
	while ((c = getc(fp)) != EOF) {
		(*ncp)++;
		if (c == '\n')
			(*nlp)++;
		if (!isspace(c) && !in) {
			in = TRUE;
			(*nwp)++;
		} else if (isspace(c) && in)
			in = FALSE;
	}
}

/* Print nl, nw, and/or nc depending on lf, wf, and cf, respectively */
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
	printf("%s%s\n", fn[0] == '\0' ? "" : " ", fn);
}
