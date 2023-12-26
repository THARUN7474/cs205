#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
void* dynamicspace(size_t a){
	int *ptr=mmap(NULL,a,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,0,0);
	printf("mapped successfully\n");
	return ptr;
}
int check(int* a,int b,int i){
	int k=0;
	while(k<b){
		if(a[k+i]!=NULL){
			break;
		}
		k++;
	}
	if(k!=(b-1)){
		return 1;
	}
	return 0;
}
void* spaceallot(int* a,int b){
	int i=0;
	while(a[i]!=NULL){
		i++;
	}
	int k=check(a,b,i);
	while(k==1){
		while(a[i]==NULL){
			i++;
		}
		while(a[i]!=NULL){
			i++;
		}
		k=check(a,b,i);
	}
	int j=0;
	while(j<b){
		a[i+j]=0;
		j++;
	}
	printf("subspace allocated successfully\n");
	int *ptr=&a[i];
	return ptr;
}
void spacedeallot(int *a,int b){
	int i=0;
	while(i<b){
		a[i]=NULL;
		i++;
	}
	printf("subspace deallocated\n");
}
void freedynamic(void* a,size_t b){
	int err=munmap(a,b);
}	
int main(){
	int *a=(int*)dynamicspace(sizeof(int)*100);
	int pids;
	pid_t pid=fork();
	//printf("\n");
	if(pid==0){
		printf("this is child class\n");
		int *ptr=spaceallot(a,10);
		int i=0;
		printf("starting address of process in mm:%ld\n",ptr);
		while(i<5){
			ptr[i]=i;
			printf("%d\n",ptr[i]);
			printf("address:%ld\n",&ptr[i]);
			i++;
		}
		//spacedeallot(ptr,5);
	}
	else{
		wait(&pids);
		printf("this is parent process\n");
		int *ptr=spaceallot(a,10);
		printf("strating address of process in mm:%ld\n",ptr);
		int i=0;
		while(i<10){
			ptr[i]=i*100;
			printf("%d\n",ptr[i]);
			printf("address:%ld\n",&ptr[i]);
			i++;
		}
		spacedeallot(ptr,10);
	}
	exit(0);		
	freedynamic(a,sizeof(int)*100);
		printf("unmapping successed\n");
	return 1;
}