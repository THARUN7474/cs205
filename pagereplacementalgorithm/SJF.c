#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int sjf(int n,int arri[],int timere[],float *avgta,float *avgre){
    for(int i=0;i<n;i++){
        if(arri[i]>arri[i+1]){//sorting on the basis of arrival time
            int t=arri[i];
            arri[i]=arri[i+1];
            arri[i+1]=t;
            t=timere[i];
            timere[i]=timere[i+1];
            timere[i+1]=t;
        }
        if(arri[i]==arri[i+1] && timere[i]>timere[i+1]){//sorting on the basis of required time for completion of work
            int t=arri[i];
            arri[i]=arri[i+1];
            arri[i+1]=t;
            t=timere[i];
            timere[i]=timere[i+1];
            timere[i+1]=t;
        }
    }
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
        *avgta=*avgta+(timere[u]-arri[u]);
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
            *avgre=*avgre+(timere[u-1]-arri[u]);
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
    int t[n];//array for arrival time 
    int r[n];//array for required time for completion of worl
    for(int i=0;i<n;i++){
        printf("enter arrival for %d process",i+1);
        scanf("%d",&t[i]);
    }
    for(int j=0;j<n;j++){
        printf("enter time required of %d process",j+1);
        scanf("%d",&r[j]);
    }
    sjf(n,t,r,&k,&o);
    printf("Average time around time :%f\n",k);
    printf("Average response time :%f",o);
    return 0;
}