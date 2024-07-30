#include <iostream>
#include <unistd.h>
#include <string.h> // Use string.h instead of cstring for C functions

#define BUFFER_SIZE 256

using namespace std;

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[BUFFER_SIZE] = "THIS IS PARENT PROCESS"; // Correct array declaration
    char read_msg[BUFFER_SIZE]; // Correct array declaration

    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) { // Parent process
        close(fd[0]); // Close the unused read end
        write(fd[1], write_msg, strlen(write_msg) + 1); // Use strlen properly
        close(fd[1]); // Close the write end after writing
    } else { // Child process
        close(fd[1]); // Close the unused write end
        read(fd[0], read_msg, BUFFER_SIZE); // Read into read_msg
        cout << "Child read: " << read_msg << endl;
        close(fd[0]); // Close the read end after reading
    }

    return 0;
}
