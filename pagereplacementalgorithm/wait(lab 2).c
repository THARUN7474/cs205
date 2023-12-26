#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
int main(){
pid_t q;
q=fork();
if(q==0){
printf("i am child having id %d\n",q);
printf("my parent id is %d\n",getppid());
}
else{
wait(NULL);
printf("my child s id is %d",q);
printf("i am parent having id %d\n",getpid());
}
printf("common\n");
return 0;
}