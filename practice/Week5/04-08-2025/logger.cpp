#include <iostream>
#include <string>
class Logger {
public:
    virtual void log(const std::string& message) {
        std::cout << "[Generic] " << message << std::endl;
    }
};

class FileLogger : public Logger {
public:
    void log(const std::string& message) override {
        std::cout << "[File] " << message << std::endl;
    }
};

class ConsoleLogger : public Logger {
public:
    void log(const std::string& message) override {
        std::cout << "[Console] " << message << std::endl;
    }
};

void sendLog(Logger* logger, std::string msg) {
    logger->log(msg);
}

int main() {
    FileLogger f;
    ConsoleLogger c;
    sendLog(&f, "this is file logging");
    sendLog(&c, "this is consoleLogging");
}
