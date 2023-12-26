include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
#define BUFFERSIZE 100
#define read_end 0
#define write_end 1
int main(){
    char writebuffer[]="hello";
    char readbuffer[BUFFERSIZE];
    int fd[2],k;
    pid_t pid;
    if(pipe(fd)==-1){
        fprintf(stderr,"pipe failed");
    }
    pid=fork();
    if(pid==1){
        close(fd[0]);
        k=write(fd[write_end],writebuffer,BUFFERSIZE);
        close(fd[write_end]);
    } 
    else{
        wait(NULL);
        read(fd[read_end],readbuffer,k);
        printf("%s",readbuffer);
        close(fd[read_end]);
    }
    return 0;
}