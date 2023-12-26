#include <stdio.h>
#include <unistd.h>

int main(){

    int id,a,i,b;
    printf("Start of main...\n"); 
    id=fork();
    a= fork();
    b=fork();
    if (id > 0){
        //parent process/ 
        printf("Parent section...\n");
        printf("Printing the numbers from 1 to 10\n");
        for (int i = 6; i <= 10; i++){
            printf("%d", i);}
            printf("\n");
    }
    else if (id == 0){
        //child process/ 
        printf("\nfork created...\n"); 
        printf("Printing the numbers from 1 to 10\n");
        for (int i = 1; i <= 5; i++){
            printf("%d ", i);}
        printf("\n");  
    }
    else {
        //fork creation failed
        printf("\nfork creation failed!!!\n");
    }
    printf("End of the main function...\n");
    return 0;
}
