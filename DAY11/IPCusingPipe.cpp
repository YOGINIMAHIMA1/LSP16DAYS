#include <iostream>
#include <unistd.h>
#include <cstring>

int main() {
    int pipe_fd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[100];

    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid > 0) {  // Parent process
        close(pipe_fd[0]);  // Close the unused read end
        write(pipe_fd[1], write_msg, strlen(write_msg) + 1);
        close(pipe_fd[1]);
    } else {  // Child process
        close(pipe_fd[1]);  // Close the unused write end
        read(pipe_fd[0], read_msg, sizeof(read_msg));
        std::cout << "Child read from pipe: " << read_msg << std::endl;
        close(pipe_fd[0]);
    }

    return 0;
}
