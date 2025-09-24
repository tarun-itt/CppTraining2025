#include <iostream>
#include <limits>
#include <thread>
#include <chrono>

#include "Core/ElevatorSystem.h"
#include "Core/ElevatorSystemConfig.h"

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

        do{
            config.numberOfFloors = getInput("Enter the number of floors: ");
            config.numberOfBasements = getInput("Enter the number of basements: ");
            config.numberOfElevators = getInput("Enter the number of elevators: ");  
            
            std::cout << "Enter the input file name: ";
            std::getline(std::cin, config.inputFilePath);
            
        } while (!config.isValid());

        ElevatorSystem system(config);

        system.start();
        system.waitForShutdown();

    } catch (const std::exception& e) {
        std::cerr << "An exception occurred while starting the elevator system: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}