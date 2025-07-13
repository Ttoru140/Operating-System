// write a c program to show how data inconsistency can be created by the cobcurrent update of a global 
// variable and solved by mutex in a multithread process. main thread will wait for its child threads to be terminated


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_ITERATIONS 100000

int counter = 0; // Global variable shared among threads
pthread_mutex_t lock; // Mutex lock

// Function without mutex (to show inconsistency)
void* increment_without_mutex(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        counter++; // This is NOT thread-safe
    }
    return NULL;
}

// Function with mutex (solves inconsistency)
void* increment_with_mutex(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&lock);    // Lock before critical section
        counter++;                    // Critical section
        pthread_mutex_unlock(&lock);  // Unlock after critical section
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    printf("=== Demonstrating Data Inconsistency ===\n");

    // Reset counter
    counter = 0;

    // Spawn threads without mutex
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_without_mutex, NULL);
    }

    // Wait for all threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter without mutex = %d (Expected: %d)\n\n",
           counter, NUM_THREADS * NUM_ITERATIONS);

    // Now, solve using mutex
    printf("=== Solving Using Mutex ===\n");

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    // Reset counter
    counter = 0;

    // Spawn threads with mutex protection
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_with_mutex, NULL);
    }

    // Wait for all threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter with mutex = %d (Expected: %d)\n",
           counter, NUM_THREADS * NUM_ITERATIONS);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
