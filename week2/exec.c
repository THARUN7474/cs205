#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/wait.h>


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
        char *myargs[3];
        myargs[0]=strdup("wc");//initialise wc programm as child program in myarg[0]
        myargs[1]=strdup("exec.c");//its an argument that file wich we nedd to count
        myargs[2]=NULL;//marks end of array of myargs
        execvp(myargs[0],myargs);//runs the wordcount programm on file code3.c
        //we get  in order of no of lines ,words,bytes used for the file code3.c
    }
    else {
        int id_wait=wait(NULL);
        //parent process/
        printf("This is parent section of %d [id_wait:%d] [Process id: %d].\n",id,id_wait,getpid());
    }

    return 0;
}