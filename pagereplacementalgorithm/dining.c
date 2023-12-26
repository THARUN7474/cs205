#include<stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

    typedef struct
{
    sem_t *arr;
    int n;
    int i;//philospher id
} mul;

void *eatphilosopher(void *arg)
{
    mul *data = (mul *)arg;
    int n = data->n;
    int i = data->i;
    sem_t *s = data->arr;

    if (i == n - 1)
    {
        sem_wait(&s[(i + 1) % n]);
        printf("philosopher %d is thinking\n", i);
        sem_wait(&s[i]);
        printf("philosopher %d is eating\n", i);
        sem_post(&s[i]);
        sem_post(&s[(i + 1) % n]);
    }
    else
    {
        sem_wait(&s[i]);
        printf("philosopher %d is thinking\n", i);
        sem_wait(&s[(i + 1) % n]);
        printf("philosopher %d is eating\n", i);
        sem_post(&s[i]);
        sem_post(&s[(i + 1) % n]);
    }

    pthread_exit(NULL);
}

int main()
{
    sem_t s[5];
    for (int i = 0; i < 5; i++)
    {
        sem_init(&s[i], 0, 1);
    }
    pthread_t t1, t2, t3, t4, t5;
    mul td1;
    td1.arr = s;
    td1.n = 5;
    td1.i = 0;

    mul td2;
    td2.arr = s;
    td2.n = 5;
    td2.i = 1;

    mul td3;
    td3.arr = s;
    td3.n = 5;
    td3.i = 2;

    mul td4;
    td4.arr = s;
    td4.n = 5;
    td4.i = 3;

    mul td5;
    td5.arr = s;
    td5.n = 5;
    td5.i = 4;

    pthread_create(&t1, NULL, eatphilosopher, &td1);
    pthread_create(&t2, NULL, eatphilosopher, &td2);
    pthread_create(&t3, NULL, eatphilosopher, &td3);
    pthread_create(&t4, NULL, eatphilosopher, &td4);
    pthread_create(&t5, NULL, eatphilosopher, &td5);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);

    for (int i = 0; i < 6; i++)
    {
        sem_destroy(&s[i]);
    }

    return 0;
}