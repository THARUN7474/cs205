#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void sigintHandler(int signum) {
    printf("Received SIGINT signal (Ctrl+C)\n");
    exit(signum);
}
int main() {
    signal(SIGINT, sigintHandler);
    printf("Press Ctrl+C to send a SIGINT signal...\n");
    while (1) {
        printf("hello");
        sleep(1);
    }
    return 0;
}