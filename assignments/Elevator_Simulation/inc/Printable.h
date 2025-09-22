#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <chrono>
#include <optional>
#include <string>

class Printable;

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

    DisplayProperties(const Position &pos = {}, ConsoleColor fg = ConsoleColor::White, ConsoleColor bg = ConsoleColor::Black, bool isBold = false, std::chrono::milliseconds duration = std::chrono::milliseconds(0))
        : position(pos), foregroundColor(fg), backgroundColor(bg), bold(isBold),
        displayDuration(duration) {}
};

enum class RenderOperation { None, Display, Clear, Remove };

struct RenderRequest {
    RenderOperation operationType;
    Printable *object = nullptr;
    std::string printableId;

    RenderRequest(): operationType(RenderOperation::None), object(nullptr), printableId("") {}
    RenderRequest(RenderOperation operationType, Printable *object, std::string printableId): operationType(operationType), object(object), printableId(printableId) {}

    explicit operator bool() const noexcept {
        return operationType != RenderOperation::None;
    }
};

class Printable {
    public:
        virtual ~Printable() = default;
        virtual std::string getContent() const = 0;
        virtual DisplayProperties getDisplayProperties() const = 0;
};

#endif