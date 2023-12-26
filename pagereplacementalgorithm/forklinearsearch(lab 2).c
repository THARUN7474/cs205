#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>
int main(){
    clock_t start,end;
    int arr[100000],data=99999;
    int p_id;
    for(int i=0;i<100000;i++){
        arr[i]=i;
    }
    int n=fork();
    start=clock();
    if(n==0){
    for(int i=0;i<50000;i++){
        if(arr[i]==data){
            printf("element found at %d",i);
            break;
        }
    }
    exit(0);
}   else{
        for(int i=50000;i<100000;i++){
            if(arr[ki]==data){
                printf("element found at %d",i);
                break;
             }
        }
    }
    wait(&p_id);
    end=clock();
    double used_time=((double)(end-start))/CLOCKS_PER_SEC;
    printf("execution_time:%le",used_time);
    return 0;
}
