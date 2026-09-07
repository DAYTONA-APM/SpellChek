#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "tree.h"
#include "words.h"

int main(int argc, char **argv)
{
    char **store;
    node *tree;
    int count;
    int i;
    int search_loops;
    struct timeval start_time;
    struct timeval end_time;
    long load_microseconds;
    long search_microseconds;

    if (argc < 2) {
        fprintf(stderr, "Error: Missing dictionary file path.\n");
        fprintf(stderr, "Usage: %s <dictionary_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    count = 0;
    search_loops = 100000;
    tree = NULL;

    /* 1. Measure Dictionary Loading and Shuffling Time */
    gettimeofday(&start_time, NULL);
    
    store = load_words(argv[1], &count);
    if (!store) {
        fprintf(stderr, "Error: Could not open dictionary file.\n");
        return EXIT_FAILURE;
    }

    /* Run your native Fisher-Yates array shuffling logic */
    randomize(store, count);

    /* Construct the Binary Search Tree */
    for (i = 0; i < count; i++) {
        addtree(&tree, store[i]);
    }

    gettimeofday(&end_time, NULL);
    
    /* Calculate microsecond difference for loading */
    load_microseconds = (end_time.tv_sec - start_time.tv_sec) * 1000000 + 
                        (end_time.tv_usec - start_time.tv_usec);

    /* 2. Measure Search Performance over a massive loop */
    gettimeofday(&start_time, NULL);
    
    for (i = 0; i < search_loops; i++) {
        /* Run a high-speed search index verification check */
        check_word(tree, "apple");
    }

    gettimeofday(&end_time, NULL);

    search_microseconds = (end_time.tv_sec - start_time.tv_sec) * 1000000 + 
                         (end_time.tv_usec - start_time.tv_usec);

    /* 3. Output Performance Analytics metrics */
    printf("\n=== Performance Benchmark Summary ===\n");
    printf("Total Words Indexed:  %d\n", count);
    printf("Tree Construction:    %ld microseconds\n", load_microseconds);
    printf("Search Loops Run:     %d\n", search_loops);
    printf("Total Lookup Time:    %ld microseconds\n", search_microseconds);
    printf("Average Latency:      %.4f microseconds per word\n", 
           (double)search_microseconds / search_loops);
    printf("======================================\n");

    /* Free memory footprint cleanly */
    free_tree(tree);
    freearr(store, count);

    return EXIT_SUCCESS;
}

