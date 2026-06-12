#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 20
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
int in = 0;   // next free slot
int out = 0;  // next full slot
int count = 0; // number of items in buffer

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < NUM_ITEMS; ++i) {
        // simulate work
        usleep(rand() % 100000);
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            // buffer full, wait for consumer
            pthread_cond_wait(&not_full, &mutex);
        }
        buffer[in] = i;
        in = (in + 1) % BUFFER_SIZE;
        ++count;
        printf("Producer %d produced item %d (count=%d)\n", id, i, count);
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < NUM_ITEMS; ++i) {
        // simulate work
        usleep(rand() % 150000);
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            // buffer empty, wait for producer
            pthread_cond_wait(&not_empty, &mutex);
        }
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        --count;
        printf("Consumer %d consumed item %d (count=%d)\n", id, item, count);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(void) {
    pthread_t prod[NUM_PRODUCERS];
    pthread_t cons[NUM_CONSUMERS];
    int prod_ids[NUM_PRODUCERS];
    int cons_ids[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        prod_ids[i] = i;
        pthread_create(&prod[i], NULL, producer, &prod_ids[i]);
    }
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        cons_ids[i] = i;
        pthread_create(&cons[i], NULL, consumer, &cons_ids[i]);
    }
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(prod[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(cons[i], NULL);
    }
    return 0;
}
