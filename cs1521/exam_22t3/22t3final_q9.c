// COMP1521 22T3 ... final exam, question 9

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <pthread.h>

#include "22t3final_q9.h"

/* Constants */
// DO NOT MODIFY THESE CONSTANTS.

// Number of possible combinations provided in each file.
#define POSSIBLE_COMBINATIONS 2880
// Number of characters in each line of the input file (including newline).
#define LINE_LENGTH 10
// Expected result of the expression.
#define EXPECTED_RESULT 10
// Number of threads to create.
#define NUM_THREADS 5

void *my_thread(void *data) {
    // You MUST call this function from every thread you create.
    compute_thread_hello();

    int line_count = POSSIBLE_COMBINATIONS / NUM_THREADS;

    int counter = 0;
    char line[LINE_LENGTH + 1];
    while (fgets(line, LINE_LENGTH + 1, (FILE *)data) != NULL && line_count > 0) {
        line_count--;
        counter += double_equals(evaluate_expression(line), EXPECTED_RESULT);
    }

    fclose((FILE *)data);
    return (void *)(long)counter;
}


int my_main(int argc, char *argv[]) {
    assert(argc == 2);

    // TODO: modify this code to split the work evenly across multiple threads.

    FILE *stream = fopen(argv[1], "r");
    if (stream == NULL) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    pthread_t thread[NUM_THREADS];
    // create multiple threads to join later, each with their own address so that they can 
    // be executed in parallel
    for (int i = 0; i < NUM_THREADS; i++) {
        FILE *thread_stream = stream;
        if (i != 0) {
            thread_stream = fopen(argv[1], "r");
            if (thread_stream == NULL) {
                perror(argv[1]);
                exit(EXIT_FAILURE);
            }
            fseek(thread_stream, (POSSIBLE_COMBINATIONS / NUM_THREADS) * i * LINE_LENGTH, SEEK_SET);
        }
        pthread_create(&thread[i], NULL, my_thread, thread_stream);
    }

    int total_counter = 0;
    for (int j = 0; j < NUM_THREADS; j++) {
        int thread_counter;
        pthread_join(thread[j], (void **)&thread_counter);
        total_counter += thread_counter;
    }   
    
    printf("%d results found!\n", total_counter);

    return 0;
}
