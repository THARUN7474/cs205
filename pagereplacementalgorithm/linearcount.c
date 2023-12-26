#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/shm.h>
#define size 100000

typedef struct
{
    int *arr;
    int lower;
    int upper;
    int key;
    int count;
}mul;

void *linearsearch(void *p){
    mul *args=(mul *) p;
    for(int i=args->lower;i<args->upper;i++){
        if(*((args->arr)+i)==args->key){
            (args->count)++;
        }
    }
    return NULL;
}



int main(){
    int arr[size];
    for(int i=0;i<size;i++){
        if(i%3==0){
            arr[i]=5000;
        }
        else{
            arr[i]=i;
        }
    }
    int count = 0;
    mul thread1;
    thread1.arr=arr;
    thread1.lower=0;
    thread1.upper=50000;
    thread1.key=5000;
    thread1.count=count;
    mul thread2;
    thread2.arr=arr;
    thread2.lower=50001;
    thread2.upper=100000;
    thread2.key=5000;
    thread2.count=count;
  
    pthread_t t1,t2;
    pthread_create(&t1,NULL,linearsearch,&thread1);
    pthread_create(&t2,NULL,linearsearch,&thread2);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("count : %d",count);
    return 0;
}