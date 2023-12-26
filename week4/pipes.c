#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2]; // File descriptors for the pipe

    if (pipe(pipefd) == -1) { // Create the pipe
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork(); // Create a child process

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    

    if (pid == 0) { // Child process
        close(pipefd[0]); // Close the read end of the pipe in the child

        // Write data to the pipe
        const char *message = "Hello, parent!";
        write(pipefd[1], message, sizeof(message));
        close(pipefd[1]); // Close the write end of the pipe in the child
    } else { // Parent process
        close(pipefd[1]); // Close the write end of the pipe in the parent

        // Read data from the pipe
        char buffer[100];
        ssize_t numBytes = read(pipefd[0], buffer, sizeof(buffer));
        if (numBytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Received message from child: %.*s\n", (int)numBytes, buffer);
        close(pipefd[0]); // Close the read end of the pipe in the parent
    }

    return 0;
}