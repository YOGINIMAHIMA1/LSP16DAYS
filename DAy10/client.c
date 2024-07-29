#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Hello from client";
    char buffer[BUFFER_SIZE] = {0};

    // Initialize OpenSSL
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation error");
        exit(EXIT_FAILURE);
    }

    // Setup server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "SERVER_IP_ADDRESS", &serv_addr.sin_addr) <= 0) {
        perror("invalid address / address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Create SSL context
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        perror("SSL_CTX_new");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Create SSL structure and connect to server
    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        close(sock);
        SSL_free(ssl);
        exit(EXIT_FAILURE);
    }

    // Send message to server
    SSL_write(ssl, message, strlen(message));
    printf("Message sent: %s\n", message);

    // Read response from server
    int valread = SSL_read(ssl, buffer, BUFFER_SIZE);
    printf("Received from server: %s\n", buffer);

    close(sock);
    SSL_free(ssl);
    EVP_cleanup();
    return 0;
}
