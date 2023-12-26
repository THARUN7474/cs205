#include<stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

    typedef struct
{
    sem_t *mutex;
    sem_t *wrt;
    int i;
    int *readcount;
} read;

typedef struct
{
    sem_t *wrt;
    int i;
} write;

void *writer(void *arg)
{ 
    write *w = (write *)arg;
    printf("writer %d is waiting\n",w->i);
    sem_wait(w->wrt);
    printf("writer %d is writing\n", w->i); 
    sem_post(w->wrt);
    pthread_exit(NULL);
}

void *reader(void *arg)
{ 
    read *r = (read *)arg;
    printf("reader %d is waiting\n",r->i);
    sem_wait(r->mutex);
    (*(r->readcount))++;
    if ((*(r->readcount)) == 1)
    { 
        sem_wait(r->wrt);
    }
    sem_post(r->mutex);

    printf("reader %d is reading\n", r->i);

    sem_wait(r->mutex);
    (*(r->readcount))--;
    if ((*(r->readcount)) == 0)
    {                 
        sem_post(r->wrt); 
    }
    sem_post(r->mutex);
    pthread_exit(NULL);
}

int main()
{
    sem_t wrt, mutex;
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);
    int count = 0;

    pthread_t t1, t2, t3, t4, t5;
    write td1 = {.wrt = &wrt, .i = 1};
    write td2 = {.wrt = &wrt, .i = 2};
    read td3 = {.mutex = &mutex, .wrt = &wrt, .i = 1, .readcount = &count};
    read td4 = {.mutex = &mutex, .wrt = &wrt, .i = 2, .readcount = &count};
    read td5 = {.mutex = &mutex, .wrt = &wrt, .i = 3, .readcount = &count};

    pthread_create(&t1, NULL, writer, &td1);
    pthread_create(&t2, NULL, writer, &td2);
    pthread_create(&t3, NULL, reader, &td3);
    pthread_create(&t4, NULL, reader, &td4);
    pthread_create(&t5, NULL, reader, &td5);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);

    return 0;
}