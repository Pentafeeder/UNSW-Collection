#include <pthread.h>
#include "thread_chain.h"

void *my_thread(void *data) {
    int counter = *((int *)data);
    thread_hello();

    if (counter < 50) {
        counter += 1;
        
        pthread_t thread_handle;
        pthread_create(&thread_handle, NULL, my_thread, (void *)&counter);

        pthread_join(thread_handle, NULL);

    }
    
    
    return NULL;
}

void my_main(void) {
    pthread_t thread_handle;
    int counter = 1;
    pthread_create(&thread_handle, NULL, my_thread, (void *)&counter);

    pthread_join(thread_handle, NULL);
}
