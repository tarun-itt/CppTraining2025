#ifndef DISPLAY_PROPERTIES_H
#define DISPLAY_PROPERTIES_H

#include <chrono>

enum class ConsoleColor {
    Reset = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    White = 37
};

struct Position {
    int x = 0;
    int y = 0;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
};

struct DisplayProperties {
    Position position;
    ConsoleColor foregroundColor = ConsoleColor::White;
    ConsoleColor backgroundColor = ConsoleColor::Black;
    bool bold = false;
    std::chrono::milliseconds displayDuration;

    DisplayProperties(const Position &pos = {}, ConsoleColor fg = ConsoleColor::White, ConsoleColor bg = ConsoleColor::Black, bool isBold = false, std::chrono::milliseconds duration = std::chrono::milliseconds(0)) //duration = 0 means object will be displayed forever
        : position(pos), foregroundColor(fg), backgroundColor(bg), bold(isBold),
        displayDuration(duration) {}
};

#endif