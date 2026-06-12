#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

#ifdef _WIN32
#include <windows.h>

typedef HANDLE pthread_t;
typedef CRITICAL_SECTION pthread_mutex_t;
typedef HANDLE sem_t;
typedef DWORD (WINAPI *thread_start_t)(LPVOID);
#define THREAD_RETURN DWORD WINAPI
#define THREAD_ARG LPVOID

#define sleep(x) Sleep((x) * 1000)

static int sem_init(sem_t* sem, int pshared, unsigned int value) {
    (void)pshared;
    *sem = CreateSemaphore(NULL, value, BUFFER_SIZE, NULL);
    return *sem ? 0 : -1;
}

static int sem_wait(sem_t* sem) {
    return WaitForSingleObject(*sem, INFINITE) == WAIT_OBJECT_0 ? 0 : -1;
}

static int sem_post(sem_t* sem) {
    return ReleaseSemaphore(*sem, 1, NULL) ? 0 : -1;
}

static int sem_destroy(sem_t* sem) {
    return CloseHandle(*sem) ? 0 : -1;
}

#define pthread_mutex_init(m, attr) InitializeCriticalSection(m)
#define pthread_mutex_lock(m) EnterCriticalSection(m)
#define pthread_mutex_unlock(m) LeaveCriticalSection(m)
#define pthread_mutex_destroy(m) DeleteCriticalSection(m)

static int pthread_create(pthread_t* thread, const void* attr, thread_start_t start_routine, void* arg) {
    (void)attr;
    *thread = CreateThread(NULL, 0, start_routine, arg, 0, NULL);
    return *thread ? 0 : -1;
}

static int pthread_join(pthread_t thread, void** retval) {
    (void)retval;
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    return 0;
}
#else
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

typedef void* (*thread_start_t)(void*);
#define THREAD_RETURN void*
#define THREAD_ARG void*
#endif

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 5; i++) {
        int item = rand() % 100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d produced %d at position %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 5; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d consumed %d from position %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t p1, p2, c1, c2;
    int id1 = 1, id2 = 2;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p1, NULL, producer, &id1);
    pthread_create(&p2, NULL, producer, &id2);
    pthread_create(&c1, NULL, consumer, &id1);
    pthread_create(&c2, NULL, consumer, &id2);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(c1, NULL);
    pthread_join(c2, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
