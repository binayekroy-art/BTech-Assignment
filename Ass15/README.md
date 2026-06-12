# Assignment 15

Write a multithreaded C program using POSIX threads (pthread) where multiple threads increment a shared global counter variable many times.

**Part 1 – No synchronization**
```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4
#define INCREMENTS 1000000

long counter = 0; // shared global counter

void *increment(void *arg) {
    for (long i = 0; i < INCREMENTS; ++i) {
        counter++; // race condition!
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    printf("Final counter (no sync): %ld\n", counter);
    return 0;
}
```
Running this program usually yields a value **less** than `NUM_THREADS * INCREMENTS` because of the race condition.

**Part 2 – Mutex synchronization**
```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4
#define INCREMENTS 1000000

long counter = 0; // shared global counter
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *increment(void *arg) {
    for (long i = 0; i < INCREMENTS; ++i) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    printf("Final counter (with mutex): %ld\n", counter);
    pthread_mutex_destroy(&lock);
    return 0;
}
```
With the mutex protecting the critical section, the final counter equals `NUM_THREADS * INCREMENTS`.

**Why the race condition occurs**
The increment operation `counter++` is not atomic; it consists of a read, modify, and write sequence. When multiple threads interleave these steps, updates can be lost.

**How the mutex solves it**
`pthread_mutex_lock` ensures only one thread executes the critical section at a time, making the increment operation effectively atomic and preserving all increments.
