#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(clientAddr);
    ssize_t recv_len;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the port
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is running and waiting for messages on port " << PORT << "...\n";

    // Loop to listen for incoming messages
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);

        // Receive message from client
        recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddr, &addr_len);
        if (recv_len < 0) {
            perror("Receive failed");
            break;
        }

        // Print received message and client information
        std::cout << "Received message: " << buffer << " from "
                  << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << "\n";

        // Send acknowledgment to client
        const char *ack = "Message received";
        if (sendto(sockfd, ack, strlen(ack), 0, (struct sockaddr *)&clientAddr, addr_len) < 0) {
            perror("Send acknowledgment failed");
            break;
        }
    }

    // Clean up resources
    close(sockfd);
    return 0;
}
