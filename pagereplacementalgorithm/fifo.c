#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int fifo(int n,int timere[],float *avgta,float *avgre){
    int u=0;
    int k=0;
    while(u!=n){
        k=k+timere[u];
        timere[u]=k;
        u++;
    }
    u=0;
    *avgta=0;//average turn around time
    while(u!=n){
        *avgta=*avgta+(timere[u]);
        u++;
    }
    *avgta=*avgta/n;        
    u=0;
    *avgre=0;//average response time
    while(u!=n){
        if(u==0){
            u++;
        }
        else{
            *avgre=*avgre+(timere[u-1]);
            u++;
        }
    }
    *avgre=*avgre/n;
}
int main(){
    float k,o;
    int n;
    printf("enter number of process");
    scanf("%d",&n); 
    int r[n];//array for required time for completion of worl
    for(int j=0;j<n;j++){
        printf("enter time required of %d process",j+1);
        scanf("%d",&r[j]);
    }
    fifo(n,r,&k,&o);
    printf("Average time around time :%f\n",k);
    printf("Average response time :%f",o);
    return 0;
}