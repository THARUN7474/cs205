
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

//creating a copy of a pragram as child of parent using fork
//here after fork()creates a child process it runs after parent process
//due to creation of child process time to do for task is divided by 2
//n frok()'s creates 2^n processes including prarent process
//so parent processs outputs print 1st and then child process 
//getpid() gives process identifier of that process

int main(int argc,char *argv[]){

    int id;
    printf("Hello, World! (pid;%d)\n",(int)getpid());

    id = fork();
    if (id < 0) {
        //fork creation failed/
        printf("fork creation failed!!!\n");
        exit(1);
    }
    else if (id == 0) {
        //child process/
        printf("fork created (hello i am child)[Process id: %d].\n", getpid());
        printf("fork parent process id: %d.\n", getpid());
    }
    else {
        // process/
        printf("This is parent section of %d [Process id: %d].\n",id, getpid());
    }

    return 0;
}
