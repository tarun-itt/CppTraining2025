#include <iostream>
#include <csignal>
#include <unistd.h>

bool shouldExit = false;

void signalHandler(int sig) {
    if (sig == SIGKILL) {
        std::cout << "\n[Signal] Caught SIGINT \n";
        shouldExit = true; 
    }
}

int main() {
    std::signal(SIGKILL, signalHandler);   

    std::cout << "Press Ctrl+C to trigger SIGINT.\n";

    int i = 0;
    while (true) {
        std::cout << "Alive: " << i++ << "\n";
        sleep(1);

        if (shouldExit) {
            std::cout << "Exiting ...\n";
            break;
        }
    }

    return 0;
}