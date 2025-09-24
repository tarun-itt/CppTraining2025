#ifndef ELEVATOR_SYSTEM_PRINTABLE_H
#define ELEVATOR_SYSTEM_PRINTABLE_H

#include <vector>
#include <string>

#include "Display/IPrintable.h"
#include "Core/ElevatorSnapshot.h"

class ElevatorSystemPrintable : public IPrintable {
public:
    explicit ElevatorSystemPrintable(std::vector<ElevatorSnapshot> snapshots);

    std::string getContent() const override;
    DisplayProperties getDisplayProperties() const override;

private:
    const int ID_WIDTH       = 3;
    const int FLOOR_WIDTH    = 4;
    const int STATE_WIDTH    = 8;
    const int DIR_WIDTH      = 9;
    const int UP_WIDTH       = 11;
    const int DOWN_WIDTH     = 14;
    
    std::vector<ElevatorSnapshot> snapshots;
};

#endif