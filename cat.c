#include <stdio.h>
#include <string.h>

void filecopy(FILE *ifp, FILE *ofp);

/* Concatenate files */
int main(int argc, char **argv)
{
	FILE *fp;

	if (argc == 1)
		filecopy(stdin, stdout);
	else
		while (--argc > 0) {
			argv++;
			if (strcmp(*argv, "-") == 0)
				filecopy(stdin, stdout);
			else if ((fp = fopen(*argv, "r")) == NULL) {
				fprintf(stderr, "cat: can't open file %s\n",
					*argv);
				return 1;
			} else {
				filecopy(fp, stdout);
				if (fclose(fp) == EOF) {
					fprintf(stderr,
						"cat: can't close file %s\n",
						*argv);
					return 1;
				}
			}
		}
	
	if (ferror(stdout)) {
		fprintf(stderr, "cat: error writing stdout\n");
		return 2;
	}

	return 0;
}

/* Copy ifp to ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
	int c;

	while ((c = getc(ifp)) != EOF)
		putc(c, ofp);
}
