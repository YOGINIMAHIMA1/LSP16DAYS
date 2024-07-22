#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fstream>

std::ofstream file;

void handle_sigint(int sig) {
    printf("Caught signal %d using signal. Cleaning up...\n", sig);

    // Perform cleanup actions
    if (file.is_open()) {
        file << "Closing file before exit.\n";
        file.close();
    }

    printf("Cleanup done. Exiting gracefully.\n");
    exit(0); // Terminate the program
}

int main() {
    file.open("output.txt");
    if (!file.is_open()) {
        perror("Failed to open file");
        return 1;
    }
    file << "Program started. Waiting for SIGINT...\n";

    signal(SIGINT, handle_sigint); // Register signal handler using signal

    while (1) {
        file << "Running... Press Ctrl+C to trigger SIGINT\n";
        sleep(1);
    }

    return 0;
}
