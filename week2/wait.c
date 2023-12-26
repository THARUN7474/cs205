#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

//this is for wait() system call code 
// by keeping wait() child process runs and then parents process run only after waiting 
int main(int argc,char *argv[]){

    int id;
    printf("Hello, World! (pid;%d)\n",(int)getpid());

    id = fork();
    if (id < 0) {
        // creation failed/
        printf("fork creation failed!!!\n");
        exit(1);
    }
    else if (id == 0) {
        //child process/
        printf("fork created (hello i am child)[Process id: %d].\n", getpid());
        printf("fork parent process id: %d.\n", getpid());
    }
    else {
        int id_wait=wait(NULL);
        //parent process/
        printf("This is parent section of %d [id_wait:%d] [Process id: %d].\n",id,id_wait,getpid());
    }
    return 0;
}