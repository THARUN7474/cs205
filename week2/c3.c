#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#define MAXSIZE 10000

int linearsearch(int arr[],int a,int b,int data,int *pos){
    for(int i=a;i<b;i++){
        if(arr[i]==data){
            *pos=i;
            return 1;
        }
    }
    return 0;
}

int main(){
    int arr[MAXSIZE];
    for(int i=0;i<MAXSIZE;i++){
        arr[i]=i;
    }
    //ofcourse it will be sorted and binary search is useful but for sake of data we r taking likes  this
    //we can use random calls to take large data
    clock_t start_time, end_time, start1,end1;
    double cpu_time_used1;
    double cpu_time_used;
    int data;
    start1=clock();
    linearsearch(arr,0,10000,5007,&data);
    end1=clock();
    start_time=clock();
    cpu_time_used1=((double)(end1-start1))/CLOCKS_PER_SEC;
    printf("THE PROCESS TO CPU TIME OF no fork case ; %f secs\n",cpu_time_used1);
    if(fork()==0){
        linearsearch(arr,0,5000,5007,&data);
    }
    else{
        linearsearch(arr,5001,10000,5007,&data);
    }
    end_time=clock();
    cpu_time_used=((double)(end_time-start_time))/CLOCKS_PER_SEC;
    printf("THE PROCESS TO CPU TIME OF ; %f secs\n",cpu_time_used);
    return 0;
}
