#ifndef WORDS_H
#define WORDS_H

#include <stddef.h>

void printarr(char **, int);
char **load_words(char *, int *);
int sort_wrds(const void *, const void *);
void swap(char **, char **);
void randomize(char **arr, int size);
void freearr(char **, int);

#endif
