#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handleClient(int client_socket, SSL *ssl) {
    char buffer[BUFFER_SIZE] = {0};
    int valread;

    // Read data from the client
    valread = SSL_read(ssl, buffer, BUFFER_SIZE);
    if (valread < 0) {
        perror("SSL_read");
        close(client_socket);
        SSL_free(ssl);
        pthread_exit(NULL);
    }
    printf("Received from client: %s\n", buffer);

    // Echo back the data to the client
    SSL_write(ssl, buffer, strlen(buffer));

    close(client_socket);
    SSL_free(ssl);
    pthread_exit(NULL);
}

void *threadFunction(void *arg) {
    int client_socket = *(int *)arg;
    SSL_CTX *ctx = SSL_CTX_new(TLS_server_method());

    if (!ctx) {
        perror("SSL_CTX_new");
        close(client_socket);
        pthread_exit(NULL);
    }

    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client_socket);

    if (SSL_accept(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        close(client_socket);
        SSL_free(ssl);
        pthread_exit(NULL);
    }

    handleClient(client_socket, ssl);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Initialize OpenSSL
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the network address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // or specify the server IP address if needed
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
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

    while (1) {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // Create a new thread for each client connection
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, threadFunction, (void *)&new_socket) != 0) {
            perror("pthread_create");
            close(new_socket);
        }
    }

    close(server_fd);
    EVP_cleanup();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handleClient(int client_socket, SSL *ssl) {
    char buffer[BUFFER_SIZE] = {0};
    int valread;

    // Read data from the client
    valread = SSL_read(ssl, buffer, BUFFER_SIZE);
    if (valread < 0) {
        perror("SSL_read");
        close(client_socket);
        SSL_free(ssl);
        pthread_exit(NULL);
    }
    printf("Received from client: %s\n", buffer);

    // Echo back the data to the client
    SSL_write(ssl, buffer, strlen(buffer));

    close(client_socket);
    SSL_free(ssl);
    pthread_exit(NULL);
}

void *threadFunction(void *arg) {
    int client_socket = *(int *)arg;
    SSL_CTX *ctx = SSL_CTX_new(TLS_server_method());

    if (!ctx) {
        perror("SSL_CTX_new");
        close(client_socket);
        pthread_exit(NULL);
    }

    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client_socket);

    if (SSL_accept(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        close(client_socket);
        SSL_free(ssl);
        pthread_exit(NULL);
    }

    handleClient(client_socket, ssl);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Initialize OpenSSL
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the network address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // or specify the server IP address if needed
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
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

    while (1) {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // Create a new thread for each client connection
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, threadFunction, (void *)&new_socket) != 0) {
            perror("pthread_create");
            close(new_socket);
        }
    }

    close(server_fd);
    EVP_cleanup();
    return 0;
}
