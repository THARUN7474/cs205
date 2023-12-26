#include<stdio.h>
#include<unistd.h>
#include<time.h>

int main(){
    int a,b,c;
    printf("Enter a value = ");
    scanf("%d", &a);
    clock_t start, end;
    double runtime;
    start=clock();
    if (fork()==0){ 
        for (b=1; b<(a/2);b++){
            printf("%d ",b);
        }
    }
    else{
        for(c=(a/2);c<=a; c++){ 
            printf("%d ",c);
        }
    }
    end=clock();
    runtime=((double)(end-start))/CLOCKS_PER_SEC;
    printf("\nRuntime=%f\n", runtime);
    return 0;

}
