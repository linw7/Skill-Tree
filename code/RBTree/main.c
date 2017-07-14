#include "RBtree.h"
#include <stdio.h>
#include <ctype.h>

#define READFILE "RBinput.txt"
#define DRAWFILE "RBdrawing.svg"

void help() {
	printf(
"Commands:\n"
"\tC   - Create empty tree\n"
"\tR   - Read tree from %s\n"
"\tW   - Write tree to screen in preorder format\n"
"\tI n - Insert node with key `n' into tree\n"
"\tD n - Delete node with key `n' from tree\n"
"\tP   - draw Picture in %s\n"
"\tH   - Help\n"
"\tS   - Stop\n",
READFILE, DRAWFILE);
}

int main(int argc, char *argv[]) {
	rb_tree tree = NULL,
		tmp = NULL;
	int cmd = 0;

	printf("This is a demo for RBTree\n");
	help();
	while (cmd != EOF) {
		int arg;
		printf("$ ");
		fflush(stdout);
		/* Find the first non-whitespace character */
		while (isspace((cmd = getchar()))) {
			if (cmd == '\n') {
				/* We delete up to end of line after the
				 * switch, so put the \n back on. */
				ungetc(cmd, stdin);
				break;
			}
		}
		switch(cmd) {
		case 'C':
		case 'c':
			/* If we already had a tree, we need to free up
			 * the memory. */
			if (tree != NULL) {
				printf("Tree already exists - clearing.\n");
				RBfree(tree);
			}
			tree = RBcreate();
			break;
		case 'R':
		case 'r':
			tmp = RBread(READFILE);
			/* If there was an error, just keep the tree we
			 * have. */
			if (tmp != NULL) {
				if (tree != NULL) {
					printf("Non-empty tree - overwriting.\n");
					RBfree(tree);
				}
				tree = tmp;
			}
			break;
		case 'W':
		case 'w':
			if (tree == NULL) {
				fprintf(stderr, "Error: no tree loaded, cannot write.\n");
			} else {
				RBwrite(tree);
			}
			break;
		case 'I':
		case 'i':
			if (tree == NULL) {
				printf("No tree loaded - creating empty one.\n");
				tree = RBcreate();
			}
			if (scanf("%d", &arg) != 1) {
				fprintf(stderr, "Error: must specify integer key to insert.\n");
			} else {
				RBinsert(tree, arg);
			}
			break;
		case 'D':
		case 'd':
			if (tree == NULL) {
				fprintf(stderr, "Error: no tree loaded, cannot delete.\n");
			} else {
				if (scanf("%d", &arg) != 1) {
					fprintf(stderr, "Error: must specify integer key to delete.\n");
				} else {
					RBdelete(tree, arg);
				}
			} 
			break;
		case 'P':
		case 'p':
			if (tree == NULL) {
				fprintf(stderr, "Error: no tree loaded, cannot draw.\n");
			} else {
				RBdraw(tree, DRAWFILE);
			}
			break;
		case 'H':
		case 'h':
			help();
			break;
		case EOF:
			/* Make the shell not return on the same line */
			putchar('\n');
		case 'S':
		case 's':
			cmd = EOF;
			break;
		/* Corresponds to an empty command */
		case '\n':
			break;
		default:
			fprintf(stderr, "Error: unknown command `%c'.\n", cmd);
			help();
			break;
		}
		if (cmd != EOF) {
			/* Delete the rest of the line. */
			while ((cmd = getchar()) != '\n');
		}
	}

	/* We need to free the tree. */
	if (tree != NULL) {
		RBfree(tree);
	}
	RBcleanup();

	return 0;
}
