#define SIZE 100
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int fifo(int nops,int arrivaltime[SIZE],int reqtime[SIZE],int (*turnAT)[SIZE],int (*resPT)[SIZE],float *avgTAT,float *avgRT){
    //here arrival times and reqtime of each process will be same
    int c[SIZE];
    (*resPT)[0]=0;
    c[0]=reqtime[0];
    for(int k=1;k<nops;k++){
        c[k]=reqtime[k]+c[k-1];
    }
    for(int i=0;i<nops;i++){
        (*turnAT)[i]=(c[i]-arrivaltime[i]);
    }
    for(int j=1;j<nops;j++){
        (*resPT)[j]=(((*resPT)[j-1]+reqtime[j-1])-arrivaltime[j]);
    }
    *avgTAT=0;
    *avgRT=0;
    for(int l=0;l<nops;l++){
        *avgTAT+=(*turnAT)[l];
        *avgRT+=(*resPT)[l];
    }
    *avgTAT=(*avgTAT)/nops;
    *avgRT=(*avgRT)/nops;
    return 1;
}

int main(){
    int nops;
    int arrivaltime[SIZE],reqtime[SIZE],turnAT[SIZE],resPT[SIZE];
    float avgTAT,avgRT;
    printf("enter the no of processes need to be run:");
    scanf("%d",&nops);//here nops will be indirectly length of both arays
    for(int i=0;i<nops;i++){
        printf("enter the arravial time of %d process;",i+1);
        scanf("%d",&arrivaltime[i]);
        printf("enter the req time of %d process;",i+1);
        scanf("%d",&reqtime[i]);
    }
    fifo(nops,arrivaltime,reqtime,&turnAT,&resPT,&avgTAT,&avgRT);

    printf("\nthe individual turnaroundtimes of each process inorder\n");
    for(int k=0;k<nops;k++){
        printf("%d\t",turnAT[k]);
    }
    printf("\nthe individual responcetimes of each process inorder\n");
    for(int i=0;i<nops;i++){
        printf("%d\t",resPT[i]);
    }
    printf("\nthe avg turnaround time of all process is %f\n",avgTAT);
    printf("\ntha avg responce time of all process is %f\n",avgRT);

    return 0;
}
