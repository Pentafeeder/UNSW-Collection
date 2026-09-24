#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void *increment_and_sleep(void *arg);

void costly_addition(int num)
{
    pthread_t thread_handle;

    for (int i = 0; i < num; i++) {
        pthread_create(&thread_handle, NULL, increment_and_sleep, (void *)&num);
    }

    pthread_join(thread_handle, NULL);
}
