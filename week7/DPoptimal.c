#include<stdio.h>
#include<stdlib.h>
#define MAX 100

void optimal_code(int inputs[MAX],int len,int FS){
    int box[FS],PH=0,PF=0,key;
    int temp[FS];
    printf("\nthe box elements are");
    for(int i=0;i<FS;i++){
        box[i]=inputs[i];
        ++PF;
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
            ++PF;
            for(int n=0;n<FS;n++){
                temp[n]=len+1;
                for(int k=j+1;k<len;k++){
                    if(box[n]==inputs[k]){
                        temp[n]=k+1;
                        break;
                    }
                }
            }
            printf("\n%d,%d,%d\n",temp[0],temp[1],temp[2]);
            int max=0;int cp=0;
            for(int a=0;a<FS;a++){
                if(temp[a]>max){
                    max=temp[a];
                    cp=a;
                }
            }
            //here cp will be the position of max in temp[] so.....
            //it means that cp pos in box[] will be the farthest element or not present in inputs[] sop it will be victim
            box[cp]=key;
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
    //int inputs[MAX],a,b;
    int a,b;
    printf("\nenter the size of box(pasges loaded in frames0...FS");
    scanf("%d",&a);
    printf("\nenter the size or length of reference string");
    scanf("%d",&b);
    int inputs[MAX]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    // printf("\nenter the elements in reference string with space gap b/w them");
    // for(int i=0;i<b;i++){
    //     scanf("%d",&inputs[i]);
    // }
    optimal_code(inputs,b,a);
    return 0;
}