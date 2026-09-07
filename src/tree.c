#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "words.h"
#include <ctype.h>

#define TRUE 1
#define FALSE 0 

static node *python_tree_root = NULL; /*python wrapper var */

void addtree (node **ptr, char *word)
{
	int cmp;
	node *curr;

	curr = *ptr; /* point to the first value */

	if (curr == NULL) {
		curr = malloc(sizeof(node));
		curr->word = malloc(sizeof(char) * (strlen(word) + 1));
		if (!curr->word)
			return;
		strcpy(curr->word, word);
		curr->left = NULL;
		curr->right = NULL;

		*ptr = curr; /* change the first node */
		return;
	}

	cmp = strcmp(curr->word, word);
	if (cmp > 0)
		addtree(&(curr->left), word);
	if (cmp < 0)
		addtree(&(curr->right), word);

}

void free_tree(node *p)
{
	if (p != NULL) {
		free_tree(p->left);
		free_tree(p->right);
		free(p->word);
		free(p);
	}
}

void printtree(node **p)
{
	node *head;
	 
	if (!p || !*p)
		return;
	
	head = *p;

	printtree(&(head->left));
	printf("%s\n", head->word);
	printtree(&(head->right));
}
	
int search_tree(const node *p, char *target) 
{
    /* case 1, the tree is empty, or the word isn't there */
    int result;

    if (p == NULL) {
        return FALSE;
    } else {
        /* compare the target word to that in the current node */
        result = strcmp(target, p->word);

        /* case 2: the word is found */
        if (result == 0) {
            return TRUE;
        } else if (result < 0) {
            return search_tree(p->left, target);
        } else {
            return search_tree(p->right, target);
        }
    }
}

void toLower(char *str) {
    while (*str != '\0') {
        *str = (unsigned char)tolower(*str);
        str++;
    }
}

int check_word(const node *root, const char *target) {
	char buff[100];
	
	if (strlen(target) >= sizeof(buff))
		return FALSE;

	strcpy(buff, target);
	toLower(buff);

	return search_tree(root, buff); 
}


void py_load_dictionary(char *file_path) {
    int count;
    int i;
    char **store;

    count = 0;

    /* 1. If an older tree is already loaded, free it up cleanly */
    if (python_tree_root != NULL) {
        free_tree(python_tree_root);
        python_tree_root = NULL;
    }

    /* 2. Call your new dynamic array word loader from words.c */
    store = load_words(file_path, &count);
    if (!store) {
        return;
    }

    /* 3. Call your native C Fisher-Yates shuffle algorithm from words.c */
    randomize(store, count);

    /* 4. Loop through the randomized array and load it into your BST */
    for (i = 0; i < count; i++) {
        addtree(&python_tree_root, store[i]);
    }

    /* 5. Clean up the temporary array allocation safely */
    freearr(store, count);
}

int py_check_word(const char *word) {
    /* Calls your lowercase check_word function from tree.c */
    return check_word(python_tree_root, word);
}


