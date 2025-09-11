#include <iostream>
#include <limits>
#include <vector>

#include "ILane.h"
#include "Lane.h"
#include "Timer.h"
#include "TrafficController.h"

#define GREEN_LIGHT_DURATION 5

int main() {
    std::vector<ILane*> lanes;
    Timer timer;

    std::cout << "=============== Traffic Light Simulation ===============" << "\n\n";

    int numberOfLanes;
    std::cout << "Enter number of lanes: ";

    while(!(std::cin >> numberOfLanes && numberOfLanes >= 1 && numberOfLanes <= 26)){
        std::cout<<"Invalid Input! Please enter a number(1-26): \n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    std::cout << "Enter initial number of cars for each lane:" << std::endl;

    for (int i = 0; i < numberOfLanes; ++i) {
        std::cout << "Lane " << static_cast<char>('A' + i) << ": ";
        int carCount;
        std::cin >> carCount;
        if (carCount < 0) {
            std::cout << "Invalid number of cars. Must be non-negative." << std::endl;
            --i;
            continue;
        }
        std::string laneName = "Lane " + std::string(1, 'A' + i);
        lanes.push_back(new Lane(i, laneName, carCount));
    }

    TrafficController controller(lanes, timer, GREEN_LIGHT_DURATION);
    
    
    std::cout << "\nSimulation..." << "\n";
    std::cout << "=======================================================" << "\n";
    
    controller.run();
    
    std::cout << "\nSimulation completed!" << "\n";
    
    for (auto* lane : lanes) {
        delete lane;
    }
    
    return 0;
}