#include <iostream>
#include <limits>
#include <thread>
#include <chrono>

#include "ElevatorSystem.h"
#include "ElevatorSystemConfig.h"

int getInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.good()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Invalid input. Please enter a positive integer." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    try {
        ElevatorSystemConfig config;

        config.numberOfFloors = getInput("Enter the number of floors: ");
        config.numberOfBasements = getInput("Enter the number of basements: ");
        config.numberOfElevators = getInput("Enter the number of elevators: ");

        if (!config.isValid()) {
            std::cerr << "Configuration Error: Values must be positive. Exiting." << std::endl;
            return 1;
        }

        ElevatorSystem system(config);

        system.start();

        while (system.isRunning()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    } catch (const std::exception& e) {
        std::cerr << "FATAL ERROR: An unhandled exception occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}