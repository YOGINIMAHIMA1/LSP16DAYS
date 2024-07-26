#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <vector>
#include <signal.h>
#include <atomic>

// Global variables to handle signal termination
std::atomic<bool> server_running(true);
int server_fd;
std::vector<std::thread> client_threads;

// Function to handle client connections
void handle_client(int client_socket) {
    char buffer[1024] = {0};
    while (true) {
        int valread = read(client_socket, buffer, 1024);
        if (valread <= 0) {
            std::cout << "Client disconnected" << std::endl;
            close(client_socket);
            return;
        }
        std::cout << "Received: " << buffer << std::endl;
        send(client_socket, buffer, strlen(buffer), 0);
    }
}

// Signal handler for SIGINT and SIGTERM
void signal_handler(int signum) {
    std::cout << "Signal (" << signum << ") received, shutting down server..." << std::endl;
    server_running = false;
    close(server_fd);
    for (auto& t : client_threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    exit(signum);
}

int main() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    const int port = 9090;

    // Set up signal handling
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Prepare the sockaddr_in structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << port << std::endl;

    while (server_running) {
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            if (server_running) {
                perror("accept");
            }
            break;
        }

        std::cout << "Connection accepted" << std::endl;
        client_threads.push_back(std::thread(handle_client, new_socket));
    }

    return 0;
}
