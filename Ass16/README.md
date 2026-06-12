# Assignment 16

Develop a multithreaded C program using POSIX threads where multiple threads coordinate access to a shared resource using semaphores or condition variables. Below is a simple **producer‑consumer** example that uses a **bounded buffer**, a **mutex**, a **condition variable** for synchronization, and demonstrates proper waiting and signaling.

## Problem description
- A fixed‑size buffer holds produced items.
- Producer threads generate items and place them into the buffer.
- Consumer threads remove items from the buffer.
- If the buffer is full, producers wait until a consumer consumes an item.
- If the buffer is empty, consumers wait until a producer adds an item.

## Key functions used
- `pthread_create`, `pthread_join` – thread creation and termination.
- `pthread_mutex_t` – protects the shared buffer.
- `pthread_cond_wait`, `pthread_cond_signal` – block/wake threads based on buffer state.
- `sem_t` could also be used, but this example shows condition variables.

## How synchronization prevents inconsistency
- The **mutex** guarantees exclusive access to buffer indices and the count.
- **Condition variables** make threads block when they cannot proceed (full/empty) and wake them when the state changes, avoiding busy‑waiting and race conditions.

## Expected output (example)
```
Producer 0 produced item 0
Producer 1 produced item 1
Consumer 0 consumed item 0
Producer 0 produced item 2
Consumer 1 consumed item 1
...
```
The exact order may vary due to thread scheduling, but the program never corrupts the buffer or loses items.
