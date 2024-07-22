#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fstream>

std::ofstream file;

void handle_sigint(int sig) {
    printf("Caught signal %d using sigaction. Cleaning up...\n", sig);

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

    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0; // or SA_RESTART to restart certain interrupted system calls
    sigemptyset(&sa.sa_mask); // Block no additional signals during the handler

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    while (1) {
        file << "Running... Press Ctrl+C to trigger SIGINT\n";
        sleep(1);
    }

    return 0;
}
