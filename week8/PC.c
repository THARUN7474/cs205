
// Certainly! Classical synchronization problems in operating systems involve managing the interaction and coordination among multiple processes to ensure proper execution and resource sharing. Here are some classical synchronization problems, each explained in detail:

// 1. The Producer-Consumer Problem:
// Scenario: Imagine a bakery with producers baking bread and consumers buying it.
// Challenge: Producers should not overflow the bread shelves, and consumers should not purchase non-existent bread.
// Synchronization Mechanism: Use semaphores to control access to the shared buffer (bread shelves). Producers acquire a slot when baking, and consumers acquire a slot when buying.
// 2. The Reader-Writer Problem:
// Scenario: Consider a library with readers and writers accessing shared books.
// Challenge: Allow multiple readers to access books concurrently, but only one writer should modify the books at a time.
// Synchronization Mechanism: Use semaphores and mutex. Readers acquire a read lock, allowing multiple readers simultaneously. Writers acquire a write lock, ensuring exclusive access when writing.
// 3. The Dining Philosophers Problem:
// Scenario: Picture philosophers sitting around a dining table, either thinking or eating.
// Challenge: Prevent deadlock and resource contention as philosophers try to pick up both forks.
// Synchronization Mechanism: Use semaphores or mutex to represent forks. Philosophers must acquire both forks before eating, and a thoughtful ordering of fork acquisition prevents deadlock.

// The Producer-Consumer Problem involves coordinating the activities of two types of processes, producers and consumers, that share a common, fixed-size buffer. The challenge is to ensure that the producers do not produce items when the buffer is full, and consumers do not consume items when the buffer is empty. Synchronization mechanisms, such as semaphores, are typically used to solve this problem. Below is a solution in Python using threading and semaphores.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

sem_t mutex, full_sem, empty_sem;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100 + 1;  // Produce a random item
        sleep((rand() % 3) + 1);  // Simulate some work before producing

        sem_wait(&empty_sem);  // Wait for an empty slot
        sem_wait(&mutex);  // Enter critical section

        buffer[in] = item;  // Add item to the buffer
        printf("Produced %d. Buffer: [", item);
        for (int i = 0; i < BUFFER_SIZE; i++) {
            printf("%d ", buffer[i]);
        }
        printf("]\n");

        in = (in + 1) % BUFFER_SIZE;  // Move the index to the next position
        sem_post(&mutex);  // Exit critical section
        sem_post(&full_sem);  // Signal that a slot is now full
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full_sem);  // Wait for a full slot
        sem_wait(&mutex);  // Enter critical section

        item = buffer[out];  // Remove item from the buffer
        printf("Consumed %d. Buffer: [", item);
        for (int i = 0; i < BUFFER_SIZE; i++) {
            printf("%d ", buffer[i]);
        }
        printf("]\n");

        out = (out + 1) % BUFFER_SIZE;  // Move the index to the next position
        sem_post(&mutex);  // Exit critical section
        sem_post(&empty_sem);  // Signal that a slot is now empty

        sleep((rand() % 3) + 1);  // Simulate some work after consuming
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&full_sem, 0, 0);
    sem_init(&empty_sem, 0, BUFFER_SIZE);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (will never happen in this case)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&full_sem);
    sem_destroy(&empty_sem);

    return 0;
}

// Shared Variables:
// buffer: An array representing the shared storage where producers put items and consumers take items.
// in and out: Index variables indicating where the next item will be produced or consumed.

// Semaphores:
// mutex: A lock that ensures only one process (either producer or consumer) can access the buffer at a time.
// full_sem: Counts the number of filled slots in the buffer. It helps the consumer know when there is something to consume.
// empty_sem: Counts the number of empty slots in the buffer. It helps the producer know when there is space to produce.

// Producer Function (producer):
// Produce Item:
// Generate a random item.
// Simulate some work before producing by sleeping for a random time.
// Critical Section:
// Acquire the empty_sem semaphore to ensure there's an empty slot in the buffer.
// Acquire the mutex semaphore to enter the critical section (exclusive access to the buffer).
// Add the item to the buffer.
// Print the produced item and the current state of the buffer.
// Update the index (in) for the next production.
// Release the mutex semaphore to exit the critical section.
// Release the full_sem semaphore to signal that a slot is now full.
// Consumer Function (consumer):
// Wait for Full Slot:
// Acquire the full_sem semaphore to wait for a full slot in the buffer.
// Critical Section:
// Acquire the mutex semaphore to enter the critical section (exclusive access to the buffer).
// Remove an item from the buffer.
// Print the consumed item and the current state of the buffer.
// Update the index (out) for the next consumption.
// Release the mutex semaphore to exit the critical section.
// Release the empty_sem semaphore to signal that a slot is now empty.
// Simulate Work After Consuming:
// Sleep for a random time to simulate some work after consuming.
// Main Function (main):
// Thread Creation:
// Create threads for the producer and consumer functions.
// Semaphore Initialization:
// Initialize semaphores (mutex, full_sem, and empty_sem).
// Thread Joining:
// Wait for the threads to finish (in this case, they run indefinitely).
// Semaphore Destruction:
// Destroy the semaphores to free up resources.
// Running the Program:
// The producer and consumer threads run concurrently, and the semaphores ensure they don't interfere with each other.
// The program runs indefinitely until manually terminated.
// This solution illustrates a basic mechanism for coordinating the production and consumption of items by multiple threads, preventing issues like buffer overflow or underflow. The semaphores provide a way for threads to signal and synchronize their activities.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0, count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty_cond = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100 + 1;  // Produce a random item
        sleep((rand() % 3) + 1);  // Simulate some work before producing

        pthread_mutex_lock(&mutex);  // Enter critical section

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&empty_cond, &mutex);  // Wait if buffer is full
        }

        buffer[in] = item;  // Add item to the buffer
        printf("Produced %d. Buffer: [", item);
        for (int i = 0; i < BUFFER_SIZE; i++) {
            printf("%d ", buffer[i]);
        }
        printf("]\n");

        in = (in + 1) % BUFFER_SIZE;  // Move the index to the next position
        count++;

        pthread_cond_signal(&full_cond);  // Signal that a slot is now full
        pthread_mutex_unlock(&mutex);  // Exit critical section
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        pthread_mutex_lock(&mutex);  // Enter critical section

        while (count == 0) {
            pthread_cond_wait(&full_cond, &mutex);  // Wait if buffer is empty
        }

        item = buffer[out];  // Remove item from the buffer
        printf("Consumed %d. Buffer: [", item);
        for (int i = 0; i < BUFFER_SIZE; i++) {
            printf("%d ", buffer[i]);
        }
        printf("]\n");

        out = (out + 1) % BUFFER_SIZE;  // Move the index to the next position
        count--;

        pthread_cond_signal(&empty_cond);  // Signal that a slot is now empty
        pthread_mutex_unlock(&mutex);  // Exit critical section

        sleep((rand() % 3) + 1);  // Simulate some work after consuming
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (will never happen in this case)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}


// In this alternative solution:

// Instead of using semaphores, we use a mutex (pthread_mutex_t) and condition variables (pthread_cond_t).
// The producer and consumer threads use pthread_cond_wait and pthread_cond_signal to wait for and signal conditions, respectively.
// The count variable keeps track of the number of items in the buffer.
// pthread_cond_wait releases the mutex and puts the thread to sleep until it's awakened by a signal. It then reacquires the mutex before continuing.
// This solution demonstrates another way to achieve synchronization in the Producer-Consumer Problem using mutexes and condition variables instead of semaphores. Both approaches are valid, and the choice may depend on the specific requirements and constraints of the system.





