#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#define NUM_THREADS 5
#define INCREMENTS 1000000

long counter = 0;

#ifdef _WIN32
CRITICAL_SECTION lock;
#else
pthread_mutex_t lock;
#endif

#ifdef _WIN32
DWORD WINAPI increment(LPVOID arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        EnterCriticalSection(&lock);
        counter++;
        LeaveCriticalSection(&lock);
    }
    return 0;
}
#else
void* increment(void* arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
#endif

int main() {
#ifdef _WIN32
    HANDLE threads[NUM_THREADS];
    InitializeCriticalSection(&lock);
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = CreateThread(NULL, 0, increment, NULL, 0, NULL);
        if (threads[i] == NULL) {
            fprintf(stderr, "Failed to create thread %d\n", i);
            return 1;
        }
    }
    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);
    for (int i = 0; i < NUM_THREADS; i++) {
        CloseHandle(threads[i]);
    }
    DeleteCriticalSection(&lock);
#else
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
#endif
    printf("Final counter value (with mutex): %ld\n", counter);
    return 0;
}
