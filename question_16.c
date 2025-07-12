//Write a C program to handle racing situations in a multi-threaded process

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_ITERATIONS 100000

int counter = 0;                 // Shared global variable
pthread_mutex_t lock;           // Mutex to protect counter

void* increment(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&lock);   // Lock before accessing counter
        counter++;                   // Critical section
        pthread_mutex_unlock(&lock); // Unlock after increment
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Mutex init failed");
        return 1;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    // Print final counter value
    printf("Expected counter value: %d\n", NUM_THREADS * NUM_ITERATIONS);
    printf("Actual counter value:   %d\n", counter);

    return 0;
}
