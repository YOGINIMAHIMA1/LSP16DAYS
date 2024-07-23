 /*Problem Statement 2: Signal Masking and Unmasking for Graceful Shutdown
Problem: Develop a C++ application that gracefully handles termination signals (e.g., SIGTERM, SIGINT) by masking specific signals during critical operations and unmasking them afterwards. Implement a clean shutdown procedure that ensures all resources are released before the process exits.

Key Challenges:

Determining the appropriate signals to mask during critical operations.
Ensuring timely unmasking of signals to avoid process hangs.
Implementing a robust shutdown mechanism that handles unexpected interruptions.
*/

#include <iostream>
#include <csignal>
#include <cstring>
#include <unistd.h>
#include <cstdlib>

// Flag to indicate shutdown
volatile sig_atomic_t shutdownFlag = 0;

// Signal handler for termination signals
void terminationHandler(int signo) {
    if (signo == SIGINT) {
        std::cout << "\nSIGINT received, initiating graceful shutdown..." << std::endl;
    } else if (signo == SIGTERM) {
        std::cout << "\nSIGTERM received, initiating graceful shutdown..." << std::endl;
    }
    shutdownFlag = 1;
}

// Critical operation
void performCriticalOperation() {
    std::cout << "Starting critical operation..." << std::endl;
    
    // Block signals during the critical operation
    sigset_t blockSet;
    sigemptyset(&blockSet);
    sigaddset(&blockSet, SIGINT);
    sigaddset(&blockSet, SIGTERM);
    
    if (sigprocmask(SIG_BLOCK, &blockSet, nullptr) == -1) {
        std::cerr << "Error blocking signals: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Simulate a critical operation
    sleep(5);  // Replace this with actual work
    
    // Unblock signals after the critical operation
    if (sigprocmask(SIG_UNBLOCK, &blockSet, nullptr) == -1) {
        std::cerr << "Error unblocking signals: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::cout << "Critical operation completed." << std::endl;
}

// Cleanup function for graceful shutdown
void cleanup() {
    std::cout << "Performing cleanup tasks..." << std::endl;
    // Add cleanup code here (e.g., close files, release resources)
    std::cout << "Cleanup completed." << std::endl;
}

int main() {
    // Register signal handlers
    struct sigaction action;
    std::memset(&action, 0, sizeof(action));
    action.sa_handler = terminationHandler;
    sigaction(SIGINT, &action, nullptr);
    sigaction(SIGTERM, &action, nullptr);
    
    std::cout << "Application running. Press Ctrl+C to exit." << std::endl;

    // Main loop
    while (!shutdownFlag) {
        performCriticalOperation();
        // Perform other non-critical tasks here
    }
    
    // Perform cleanup on shutdown
    cleanup();
    std::cout << "Application exited gracefully." << std::endl;

    return 0;
}
