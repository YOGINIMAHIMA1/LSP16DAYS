#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>
#include <cstring>

const int NUM_CHILDREN = 2;
int pipes[NUM_CHILDREN][2];

void handle_signal(int sig) {
    std::cout << "Parent received signal: " << sig << std::endl;
    // Perform any necessary cleanup
    for (int i = 0; i < NUM_CHILDREN; ++i) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    exit(0);
}

void child_process(int id) {
    close(pipes[id][0]);  // Close reading end

    std::string message = "Hello from child " + std::to_string(id);
    write(pipes[id][1], message.c_str(), message.size() + 1); // Write to pipe

    close(pipes[id][1]); // Close writing end
    exit(0);
}

int main() {
    // Setup signal handler
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, nullptr);

    // Create pipes
    for (int i = 0; i < NUM_CHILDREN; ++i) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Fork child processes
    for (int i = 0; i < NUM_CHILDREN; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            child_process(i);
        }
    }

    // Parent process
    for (int i = 0; i < NUM_CHILDREN; ++i) {
        close(pipes[i][1]);  // Close writing end
    }

    for (int i = 0; i < NUM_CHILDREN; ++i) {
        char buffer[256];
        read(pipes[i][0], buffer, sizeof(buffer)); // Read from pipe
        std::cout << "Parent received: " << buffer << std::endl;
        close(pipes[i][0]); // Close reading end
    }

    // Wait for child processes to terminate
    for (int i = 0; i < NUM_CHILDREN; ++i) {
        wait(nullptr);
    }

    return 0;
}
