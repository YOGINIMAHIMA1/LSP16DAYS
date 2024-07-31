#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

int main() {
    const char* filename = "example.txt";
    const char* content = "Hello, World!";
    char buffer[256];
    ssize_t bytesRead, bytesWritten;
    int fd;

    // Create or truncate the file
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        std::cerr << "Error creating or opening file: " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    // Write to the file
    bytesWritten = write(fd, content, strlen(content));
    if (bytesWritten == -1) {
        std::cerr << "Error writing to file: " << strerror(errno) << std::endl;
        close(fd);
        return EXIT_FAILURE;
    }

    if (bytesWritten != (ssize_t)strlen(content)) {
        std::cerr << "Incomplete write to file" << std::endl;
        close(fd);
        return EXIT_FAILURE;
    }

    // Reset the file pointer to the beginning
    if (lseek(fd, 0, SEEK_SET) == -1) {
        std::cerr << "Error seeking in file: " << strerror(errno) << std::endl;
        close(fd);
        return EXIT_FAILURE;
    }

    // Read from the file
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        std::cerr << "Error reading from file: " << strerror(errno) << std::endl;
        close(fd);
        return EXIT_FAILURE;
    }

    // Null-terminate the buffer and print its contents
    buffer[bytesRead] = '\0';
    std::cout << "File contents: " << buffer << std::endl;

    // Close the file descriptor
    if (close(fd) == -1) {
        std::cerr << "Error closing file: " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    // Delete the file
    if (unlink(filename) == -1) {
        std::cerr << "Error deleting file: " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
