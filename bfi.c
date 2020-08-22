#include <limits.h>
#include <stdio.h>
#include <string.h>

enum {
	CMD_MAX = 50000,	/* Maximum number of commands */
	DATA_SIZE = 30000	/* Number of available data cells */
};

static const char valid_cmds[] = "><+-.,[]";	/* Valid brainfuck commands */

/* Read and interpret brainfuck commands from a file */
int main(int argc, char **argv)
{
	FILE *fp;			/* File containing the program */

	unsigned char cmd[CMD_MAX];	/* Array of commands read from fp */
	int ci;				/* Index into cmd */
	int ncmd;			/* Number of commands read */
	/* If x is the index of a [ command, match[0][x] is the index of the
	 * matching ] command. Vice versa for match[1][x].
	 */
	int match[2][CMD_MAX];

	unsigned char data[DATA_SIZE];	/* Array of data cells */
	int di;				/* Index into data */

	/* Temporary variables */
	int stack[CMD_MAX];		/* Stack of indexes of [ commands */
	int i, j, k, c;

	if (argc != 2) {
		fprintf(stderr, "Usage: bfi [FILE]\n");
		return 1;
	}
	if ((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "bfi: can't open file %s\n", argv[1]);
		return 1;
	}

	/* Read commands from fp into cmd, fill match */
	i = k = 0;
	while ((c = fgetc(fp)) != EOF) {
		if (i >= CMD_MAX) {
			fprintf(stderr, "bfi: too many commands\n");
			return 1;
		}
		if (strchr(valid_cmds, c) != NULL) {
			if (c == '[')
				stack[k++] = i;
			else if (c == ']') {
				int tmp;

				if (k == 0) {
					fprintf(stderr,
						"bfi: unmatched closing bracket\n");
					return 1;
				}
				tmp = stack[--k];
				match[0][tmp] = i;
				match[1][i] = tmp;
			}
			cmd[i++] = c;
		}
	}
	if (fclose(fp) == EOF) {
		fprintf(stderr, "bfi: can't close file %s", argv[1]);
		return 1;
	}
	if (k > 0) {
		fprintf(stderr, "bfi: unmatched opening bracket\n");
		return 1;
	}
	ncmd = i;

	/* Set all data cells to 0 */
	for (j = 0; j < DATA_SIZE; j++)
		data[j] = 0;

	/* Interpret commands */
	di = 0;
	for (ci = 0; ci < ncmd; ci++) {
		switch (cmd[ci]) {
		case '>':
			di++;
			if (di >= DATA_SIZE) {
				fprintf(stderr,
					"bfi: data pointer out of bounds");
				return 2;
			}
			break;
		case '<':
			di--;
			if (di < 0) {
				fprintf(stderr,
					"bfi: data pointer out of bounds");
				return 2;
			}
			break;
		case '+':
			data[di]++;
			break;
		case '-':
			data[di]--;
			break;
		case '.':
			if (putchar(data[di]) == EOF) {
				fprintf(stderr, "bfi: can't print character");
				return 2;
			}
			break;
		case ',':
			data[di] = getchar();
			break;
		case '[':
			if (data[di] == 0)
				ci = match[0][ci];
			break;
		case ']':
			if (data[di] != 0)
				ci = match[1][ci];
			break;
		default:
			/* This should never be reached */
			break;
		}
	}

	return 0;
}
