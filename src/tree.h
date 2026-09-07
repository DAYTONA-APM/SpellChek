#ifndef TREE_H
#define TREE_H

#define TRUE 1
#define FALSE 0

#include <stddef.h>

typedef struct node {
	char *word;
	struct node *left;
	struct node *right;
} node;

void addtree(node **ptr, char *wrd);
void free_tree(node *ptr);
void printtree(node **p);
int search_tree(const node *p, char *target);
void toLower(char *str);
int check_word(const node *root, const char *target);
void py_load_dictionary(char *file_path);
int py_check_word(const char *word);

#endif


