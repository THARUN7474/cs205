#include<stdio.h>
#include<stdlib.h>
#define MAX 100

void fifo_code(int inputs[MAX],int len,int FS){
    int box[FS],PH=0,PF=0,key;
    int fi=0;
    printf("\nthe box elements are");
    for(int i=0;i<FS;i++){
        box[i]=inputs[i];
        PF++;
        printf("%d\t",box[i]);
        printf("\n");
    }
    for(int j=FS;j<len;j++){
        key=inputs[j];
        int c=0;
        for(int k=0;k<FS;k++){
            if(key==box[k]){
                c=c+1;
                break;
            }
        }
        if(c==1){
            ++PH;
        }
        else{
            PF++;
            box[fi]=key;
            fi=(fi+1)%FS;
        }
        for(int m=0;m<FS;m++){
            printf("%d\t",box[m]);
        }
        printf("\n");
    }
    printf("\nthe no of page faults are %d AND page hits are %d",PF,PH);
}

int main(){
    printf("\nhello,follow along");
    int a,b;
    printf("\nenter the size of box(pasges loaded in frames0...FS");
    scanf("%d",&a);
    printf("\nenter the size or length of reference string");
    scanf("%d",&b);
    int inputs[MAX]={7,0,1,2,0,3,0,4,2,3,0,3,0,3,2,1,2,0,1,7,0,1};
    // printf("\nenter the elements in reference string with space gap b/w them");
    // for(int i=0;i<b;i++){
    //     scanf("%d",&inputs[i]);
    // }
    fifo_code(inputs,b,a);
    return 0;
}