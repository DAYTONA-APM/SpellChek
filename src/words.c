#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define INIT_CAPACITY 2

void printarr(char **words, int count);
int sort_wrds(const void *a, const void *b);
void swap (char **, char **);

char **load_words(char *filename, int *count_out)
{
	char **words;
	char **temp_words;
	int count;
	int capacity;
	FILE *fptr;
	char storage[100];
	int i;

	fptr = fopen(filename, "r");
	if (!fptr) {
		fprintf(stderr, "the file can't be found\n");
		return NULL;
	}

	capacity = 2;
	count = 0;
	words = malloc(sizeof(char *) * capacity);
	if (!words) {
		fprintf(stderr, "cannot create word array\n");
		fclose(fptr);
		return NULL;
	}

	while (fscanf(fptr, " %99s", storage) == 1) {
	   if (count >= capacity) {
			capacity *= 2;
			temp_words = realloc(words, sizeof(char *) * capacity);
			if (!temp_words) {
				fprintf(stderr, "cannot expand memory\n");
				for (i = 0; i < count; i++) {
					free(words[i]);
				} /* free collected words */
				free(words);
				fclose(fptr);
				return NULL;
			}
			words = temp_words;
		}
	   words[count] = malloc(sizeof(char) * (strlen(storage) + 1));
	   if (!words[count]){
		   fprintf(stderr, "word allocation failed\n");
			
			for (i = 0; i < count; i++) {
				free(words[i]);
			}
			free(words);
			fclose(fptr);
		   	return NULL;
		}
	   strcpy(words[count], storage);
	   count++;
	}
	fclose(fptr);
	*count_out = count;
	return words;
}		

void printarr(char **words, int count)
{
	int i;
	for (i = 0; i < count; i++)
		printf("%s ", words[i]);
	printf("\n");
}

void freearr(char **words, int count)
{
	int i;

	if (!words)
		return;

		
	for (i = 0; i < count; i++) {
		free(words[i]);
	}
	free(words);
	words = NULL;

}

int sort_wrds(const void *a, const void *b)
{
	const char **wrds1 = (const char**)a;
	const char **wrds2 = (const char**)b;

	const char *wrd1 = *wrds1;
	const char *wrd2 = *wrds2;

	return strcmp(wrd1, wrd2);
}


void swap(char **a, char **b)
{
	char *temp;

	temp = *a; /* the value of a is kept in temp */
	*a = *b;   /* the value of b is kept in a */
	*b = temp; /* now b can take on a's OG value */
}


void randomize(char **arr, int size)
{
	int j;
	int i;
	srand(time(NULL));

	for (i = size - 1; i > 0; i--) {
		j = rand() % (i+1);

		swap(&arr[i], &arr[j]);
	}
}


