#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 256

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char parent_msg[BUFFER_SIZE] = "Hello from parent!";
    char child_msg[BUFFER_SIZE] = "Hello from child!";
    char read_msg[BUFFER_SIZE];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // Parent process
        close(pipe1[0]);  // Close the read end of pipe1
        close(pipe2[1]);  // Close the write end of pipe2

        write(pipe1[1], parent_msg, strlen(parent_msg) + 1);
        close(pipe1[1]);  // Close the write end of pipe1

        read(pipe2[0], read_msg, BUFFER_SIZE);
        printf("Parent read: %s\n", read_msg);
        close(pipe2[0]);  // Close the read end of pipe2
    } else {  // Child process
        close(pipe1[1]);  // Close the write end of pipe1
        close(pipe2[0]);  // Close the read end of pipe2

        read(pipe1[0], read_msg, BUFFER_SIZE);
        printf("Child read: %s\n", read_msg);
        close(pipe1[0]);  // Close the read end of pipe1

        write(pipe2[1], child_msg, strlen(child_msg) + 1);
        close(pipe2[1]);  // Close the write end of pipe2
    }

    return 0;
}
