#include "words.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "tree.h"


int main(int argc, char **argv)
{
	char **store;
	node *tree;
	int count;
	int i;
	int result;

	if (argc < 2){
		fprintf(stderr, "file name not specified\n");
		return EXIT_FAILURE;
	}

	count = 0;
	store = load_words(argv[1], &count);
	if (!store) {
		fprintf(stderr, "file could not be opened");
		return EXIT_FAILURE;
	}

	/*printf("Initial\n");
	printarr(store, count);
	printf("Sorted\n");
	qsort(store, count, sizeof(char*), sort_wrds);
	printarr(store, count);
	printf("Shuffled\n"); */

	randomize(store, count);
	/* printarr(store, count); */

	tree = NULL;
	for (i = 0; i < count; i++) {
		 addtree(&tree, store[i]);
	}

	/* printtree(&tree); */

	result = check_word(tree, "kiwi");
	if (result == TRUE)
		printf("found\n");
	if (result == FALSE)
		printf("not found\n");

	free_tree(tree);
	freearr(store, count);

	return EXIT_SUCCESS;
}

