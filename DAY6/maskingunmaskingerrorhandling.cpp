/*Problem Statement 3: Signal Masking and Unmasking for Error Handling
Problem: Create a C++ application that uses signal masking and unmasking to handle errors gracefully. Mask specific signals during error handling routines to prevent recursive signal delivery. Implement a mechanism to log error details and perform necessary cleanup actions before re-enabling the masked signals.

Key Challenges:

Identifying the appropriate signals to mask during error handling.
Preventing infinite recursion of signal handlers.
Ensuring proper error logging and resource cleanup.*/
#include <iostream>
#include <csignal>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <fstream>

// Flag to indicate an error has occurred
volatile sig_atomic_t errorFlag = 0;

// Function to log error details
void logError(const std::string &message) {
    std::ofstream errorLog("error_log.txt", std::ios_base::app);
    if (errorLog.is_open()) {
        errorLog << message << std::endl;
        errorLog.close();
    } else {
        std::cerr << "Unable to open error log file." << std::endl;
    }
}

// Error handling signal handler
void errorHandler(int signo) {
    errorFlag = 1;
    std::string errorMessage;

    if (signo == SIGINT) {
        errorMessage = "SIGINT received: Interrupt signal.";
    } else if (signo == SIGTERM) {
        errorMessage = "SIGTERM received: Termination signal.";
    } else if (signo == SIGSEGV) {
        errorMessage = "SIGSEGV received: Segmentation fault.";
    }

    // Log the error message
    logError(errorMessage);
    std::cerr << errorMessage << std::endl;

    // Perform cleanup actions
    std::cerr << "Performing cleanup actions..." << std::endl;
    // Add cleanup code here

    // Exit program if necessary
    if (signo == SIGSEGV) {
        std::exit(EXIT_FAILURE);
    }
}

// Simulate a critical operation
void performCriticalOperation() {
    std::cout << "Performing a critical operation..." << std::endl;

    // Sleep to simulate work
    sleep(2);

    // Uncomment the next line to simulate a segmentation fault
    // *(int*)0 = 0;
}

int main() {
    // Set up the signal handler
    struct sigaction action;
    std::memset(&action, 0, sizeof(action));
    action.sa_handler = errorHandler;
    sigaction(SIGINT, &action, nullptr);
    sigaction(SIGTERM, &action, nullptr);
    sigaction(SIGSEGV, &action, nullptr);

    // Signal set to block during error handling
    sigset_t blockSet;
    sigemptyset(&blockSet);
    sigaddset(&blockSet, SIGINT);
    sigaddset(&blockSet, SIGTERM);
    sigaddset(&blockSet, SIGSEGV);

    // Main loop
    while (!errorFlag) {
        // Mask signals
        if (sigprocmask(SIG_BLOCK, &blockSet, nullptr) == -1) {
            std::cerr << "Error blocking signals: " << strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }

        // Perform critical operation
        performCriticalOperation();

        // Unmask signals
        if (sigprocmask(SIG_UNBLOCK, &blockSet, nullptr) == -1) {
            std::cerr << "Error unblocking signals: " << strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    std::cout << "Exiting application." << std::endl;
    return 0;
}
