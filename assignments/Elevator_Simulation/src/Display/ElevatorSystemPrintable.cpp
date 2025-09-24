#include <sstream>
#include <iomanip>
#include <iostream>

#include "Display/ElevatorSystemPrintable.h"
#include "Display/DisplayProperties.h"

ElevatorSystemPrintable::ElevatorSystemPrintable(std::vector<ElevatorSnapshot> snapshots)
    : snapshots(std::move(snapshots)) {}

std::string ElevatorSystemPrintable::getContent() const {
    std::stringstream table;
    table << "╔══════════════════════════════════════════════════════════════════╗\n";
    table << "║                        INPUT INSTRUCTIONS                        ║\n";
    table << "╠══════════════════════════════════════════════════════════════════╣\n";
    table << "║ Format: <from_floor> <target1> <target2> <target3> ...           ║\n";
    table << "║                                                                  ║\n";
    table << "║ Floor Types:                                                     ║\n";
    table << "║   g     - Ground floor (floor 0)                                 ║\n";
    table << "║   f1-fn - Regular floors 1-n                                     ║\n";
    table << "║   b1-bn - Basement floors -1, -n                                 ║\n";
    table << "║                                                                  ║\n";
    table << "║ Examples:                                                        ║\n";
    table << "║   f1 f7        - From floor 1 to floor 7                         ║\n";
    table << "║   f7 f4        - From floor 7 to floor 4                         ║\n";
    table << "║   b1 f5        - From basement 1 to floor 5                      ║\n";
    table << "║   g f3 f6      - From ground to floors 3 and 6                   ║\n";
    table << "║   f2 b1 f4     - From floor 2 to basement 1 and floor 4          ║\n";
    table << "║   exit         - Exit the program                                ║\n";
    table << "║                                                                  ║\n";
    table << "║ Note: You can request multiple target floors in one command      ║\n";
    table << "╚══════════════════════════════════════════════════════════════════╝\n";
    table << "\n\n";
    table << "┌──────────────────────────────────────────────────────────────────┐\n";
    table << "│                        ELEVATOR STATUS                           │\n";
    table << "├─────┬──────┬──────────┬───────────┬─────────────┬────────────────┤\n";
    table << "│ ID  │ Floor│ State    │ Direction │ Up Requests │ Down Requests  │\n";
    table << "├─────┼──────┼──────────┼───────────┼─────────────┼────────────────┤\n";

    for (const auto& snapshot : snapshots) {
        table << "│ " << std::left << std::setw(ID_WIDTH) << (snapshot.id+1);
        table << " │ " << std::right << std::setw(FLOOR_WIDTH) << snapshot.currentFloor;
    
        std::string stateStr;
        switch (snapshot.state) {
            case ElevatorState::IDLE:   stateStr = "IDLE"; break;
            case ElevatorState::MOVING: stateStr = "MOVING"; break;
            case ElevatorState::HALTED: stateStr = "HALTED"; break;
        }
        table << " │ " << std::left << std::setw(STATE_WIDTH) << stateStr;
    
        std::string dirStr;
        switch (snapshot.committedDirection) {
            case Direction::UP:   dirStr = "UP ^"; break;
            case Direction::DOWN: dirStr = "DOWN v"; break;
            case Direction::IDLE: dirStr = "IDLE"; break;
        }
        table << " │ " << std::left << std::setw(DIR_WIDTH) << dirStr;
    
        table << " │ " << std::right << std::setw(UP_WIDTH) << snapshot.upStopsCount;
        table << " │ " << std::right << std::setw(DOWN_WIDTH) << snapshot.downStopsCount << " │\n";
    }
    
    table << "└─────┴──────┴──────────┴───────────┴─────────────┴────────────────┘";
    
    return table.str();
}

DisplayProperties ElevatorSystemPrintable::getDisplayProperties() const {
    return { { 7, 4 }, ConsoleColor::White, ConsoleColor::Black, true };
}
