#include <iostream>
#include <csignal>
#include <unistd.h>

void handle_signal(int signal) {
    std::cout << "Caught signal " << signal << ", terminating gracefully." << std::endl;
    exit(0);
}

void handle_signal_usr1(int signal) {
    std::cout << "Caught SIGUSR1 signal " << signal << "." << std::endl;
}

void handle_signal_usr2(int signal) {
    std::cout << "Caught SIGUSR2 signal " << signal << "." << std::endl;
}

int main() {
    signal(SIGINT, handle_signal);
    signal(SIGUSR1, handle_signal_usr1);
    signal(SIGUSR2, handle_signal_usr2);

    std::cout << "Running... Press Ctrl+C to exit or send SIGUSR1/SIGUSR2 signals." << std::endl;
    while (true) {
        sleep(1); // Simulate work
    }
    return 0;
}
