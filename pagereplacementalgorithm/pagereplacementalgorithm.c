#include<stdio.h>
#include<stdlib.h>

int rotateList(int arr[],int size){
    int t;
        int u=arr[size-1];
        for(int j=0;j<size;j++){
                t=arr[j];
                arr[j]=u;
                u=t;
        }
    return 1;
}

int linearsearch(int arr[],int l,int size,int key){
    for(int i=l;i<size;i++){
        if(arr[i]==key){
            return i;
        }
    }
    return size+1;
}

int max(int arr[],int size){
    int may=0;
    for(int i=0;i<size;i++){
        if(arr[may]<arr[i]){
            may=i;
        }
    }
    return may;
}

int min(int arr[],int size){
    int may=0;
    for(int i=0;i<size;i++){
        if(arr[may]>arr[i]){
            may=i;
        }
    }
    return may;
}
int list(int arr[],int size){
    for(int i=0;i<size;i++){
        printf("  %d  ",arr[i]);
    }
    return 0;
}

int optimal(int arr[],int size,int pages[],int nop,int *ph,int *pf){
    int dum[size];
    for(int i=0;i<nop;i++){
        if(linearsearch(arr,0,size,pages[i])!= size+1){
            *ph+=1; 
        }
        else{
            for(int j=0;j<size;j++){
                dum[j]=linearsearch(pages,i,nop,arr[j]);
            }
            int k=max(dum,size);
            arr[k]=pages[i];
            *pf+=1;
        }
    }
    return 0;
}

int fifo(int arr[],int size,int pages[],int nop,int *ph,int *pf){
        for(int i=0;i<nop;i++){
            if(linearsearch(arr,0,size,pages[i])==size+1){
                rotateList(arr,size);
                *pf+=1;
                arr[size-1]=pages[i];
            }
            else{
                *ph+=1;
            }
        }
        return 1;
}

int linearcount(int arr[] ,int l,int size,int key){
    int count=0;
    for(int i=l;i<size;i++){
        if(arr[i]==key){
            count+=1;
        }
    }
    return count;
}

int lru(int arr[],int size,int pages[],int nop,int *ph,int *pf){
    for(int i=0;i<nop;i++){
        int pageindex=linearsearch(arr,0,size,pages[i]);
        if(linearsearch(arr,0,size,pages[i])!=size+1){
            
            for(int h=0;h<pageindex;h++){
                rotateList(arr,size);
            }
            *ph+=1;
        }
        
        else{
            rotateList(arr,size);
            arr[size-1]=pages[i];
            *pf+=1;
        }
    }
    return 0;
}

int lfu(int arr[],int size,int pages[],int nop,int *ph,int *pf){
    int dum[size];
    for(int i=0;i<nop;i++){
        if(linearsearch(arr,0,size,pages[i])!=size+1){
            *ph+=1;
        }
        else{
            *pf+=1;
            for(int j=0;j<size;j++){
                dum[j]=linearcount(arr,0,j+1,arr[j]);
            }
            int flag=0;
            for(int j=0;j<size-1;j++){
                if(dum[j]!=dum[j+1]){
                    flag=1;
                    break;
                }
            }
            if(flag==0){
                rotateList(arr,size);
                arr[size-1]=pages[i];
            }
            else{
                for(int h=0;h<min(dum,size)+1;h++){
                    rotateList(arr,size);}
                arr[size-1]=pages[i];
            }
        }
    }
    return 0;
}

int mfu(int arr[],int size,int pages[],int nop,int *ph,int *pf){
    int dum[size];
    for(int i=0;i<nop;i++){
        if(linearsearch(arr,0,size,pages[i])!=size+1){
            *ph+=1;
        }
        else{
            *pf+=1;
            for(int j=0;j<size;j++){
                dum[j]=linearcount(arr,0,j+1,arr[j]);
            }
            int flag=0;
            for(int j=0;j<size-1;j++){
                if(dum[j]!=dum[j+1]){
                    flag=1;
                    break;
                }
            }
            if(flag==0){
                rotateList(arr,size);
                arr[size-1]=pages[i];
            }
            else{
                for(int h=0;h<max(dum,size)+1;h++){
                    rotateList(arr,size);}
                arr[size-1]=pages[i];
            }
        }
    }
    return 0;
}

int main(){
    int arr[]={0,0,0};
    int size=3;
    int pages[]={1,2,5,3,5,4,2,3,5,3,2};
    int nop=11;
    int ph=0;
    int pf=0;
    lfu(arr,size,pages,nop,&ph,&pf);
    printf(" %d  %d ",ph,pf);
    return 0;
}