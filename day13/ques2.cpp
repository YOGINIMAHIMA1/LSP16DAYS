#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    const char *filename = "my_file.txt";
    char buffer[100];

    // Writing to a file
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    cout << "Enter a string to write to the file: ";
    cin.getline(buffer, sizeof(buffer));

    if (write(fd, buffer, strlen(buffer)) == -1) {
        cerr << "Error writing to file!" << endl;
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        cerr << "Error closing file after write!" << endl;
        return 1;
    }

    // Reading from the file and printing to the screen
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        cerr << "Error opening file for reading!" << endl;
        return 1;
    }

    cout << "Contents of the file:\n";
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) == -1) {
            cerr << "Error writing to stdout!" << endl;
            close(fd);
            return 1;
        }
    }
    
    if (bytesRead == -1) {
        cerr << "Error reading from file!" << endl;
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        cerr << "Error closing file after read!" << endl;
        return 1;
    }

    return 0;
}

