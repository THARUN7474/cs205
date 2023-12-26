#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define size 100000

typedef struct
{
    int *arr;
    int lower;
    int upper;
    int key;
    int *count;
    sem_t *semaphore;
} mul;

void *linearsearch(void *param)
{
    mul *p = (mul *)param;
    for (int i = p->lower; i < p->upper; i++)
    {
        if (*(p->arr + i) == p->key)
        {
            sem_wait(p->semaphore);
            (*(p->count))++;
            sem_post(p->semaphore);
        }
    }
    return NULL;
}

int main()
{
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        if (i % 3 == 0)
        {
            arr[i] = i;
        }
        else
        {
            arr[i] = i;
        }
    }

    int count = 0;
    sem_t semaphore;
    sem_init(&semaphore, 0, 1); // Initialize semaphore with initial value 1

    pthread_t thread1, thread2;

    mul td1;
    td1.arr = arr;
    td1.lower = 0;
    td1.upper = 50000;
    td1.key = 5000;
    td1.count = &count;
    td1.semaphore = &semaphore;

    mul td2;
    td2.arr = arr;
    td2.lower = 50001;
    td2.upper = 100000;
    td2.key = 5000;
    td2.count = &count;
    td2.semaphore = &semaphore;

    // Creating threads
    pthread_create(&thread1, NULL, linearsearch, &td1);
    pthread_create(&thread2, NULL, linearsearch, &td2);

    // Waiting for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("count: %d\n", count);

    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}