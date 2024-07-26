#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080

int main() {
    // Step 1: Create and write to a file
    std::ofstream outfile("example.txt");
    if (outfile.is_open()) {
        outfile << "Hello, this is a test file.\n";
        outfile.close();
    } else {
        std::cerr << "Unable to open file for writing" << std::endl;
        return 1;
    }

    // Step 2: Set up the server socket
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Step 3: Read the file and send its contents to the client
    std::ifstream infile("example.txt");
    if (infile.is_open()) {
        std::string line;
        while (getline(infile, line)) {
            send(new_socket, line.c_str(), line.size(), 0);
            send(new_socket, "\n", 1, 0);  // Send newline character
        }
        infile.close();
    } else {
        std::cerr << "Unable to open file for reading" << std::endl;
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
