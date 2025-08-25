#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <cstdlib>

int gCallCount = 0;
char* gLogBuffer = nullptr;
size_t gLogSize = 0;

typedef void (*LogFuncT)(const char*);

class FibResult {
public:
    int input;
    long result;
    time_t timestamp;

    FibResult() : input(0), result(0), timestamp(0) {}
};

FibResult* resultsArray = nullptr;
int resultsCount = 0;
int resultsCapacity = 0;

long recursiveFib(int n, LogFuncT logger);
void safeLog(const char* msg);
void unsafeLog(const char* msg);
void initLogging();
void cleanup();
void addResult(int n, long result);
void printResults();
void spinForever();

void initResults() {
    resultsCapacity = 4;
    resultsArray = new FibResult[resultsCapacity];
    if (!resultsArray) {
        std::cerr << "Failed to allocate results array\n";
        std::exit(1);
    }
    resultsCount = 0;
}

void addResult(int n, long result) {
    if (resultsCount >= resultsCapacity) {
        int newCapacity = resultsCapacity * 2;
        FibResult* newArray = new FibResult[newCapacity];
        if (!newArray) {
            return;
        }

        for (int i = 0; i < resultsCount; ++i) {
            newArray[i] = resultsArray[i];
        }
        delete[] resultsArray;
        resultsArray = newArray;
        resultsCapacity = newCapacity;
    }

    resultsArray[resultsCount].input = n;
    resultsArray[resultsCount].result = result;
    resultsArray[resultsCount].timestamp = std::time(nullptr);
    resultsCount++;
}

void printResults() {
    std::cout << "\n--- Computation History ---\n";
    for (int i = 0; i < resultsCount; ++i) {
        std::string timeStr = std::ctime(&resultsArray[i].timestamp);
        timeStr.pop_back();
        std::cout << "Fib(" << resultsArray[i].input
                  << ") = " << resultsArray[i].result
                  << " (at " << timeStr << ")\n";
    }
}

void initLogging() {
    gLogSize = 64;
    gLogBuffer = new char[gLogSize];
    if (!gLogBuffer) {
        std::cerr << "Log buffer allocation failed\n";
        std::exit(1);
    }
    gLogBuffer[0] = '\0';
}


void SLogger(const char* msg) {
    std::strcat(gLogBuffer, msg);
    std::strcat(gLogBuffer, "\n");
}

long recursiveFib(int n, LogFuncT logger) {
    char logMsg[128];
    gCallCount++;

    std::sprintf(logMsg, "recursiveFib(%d) called", n);
    logger(logMsg);

    int delay = 0;
    for (int i = 0; i < 10000; ++i) delay++;

    if (n < 0) {
        std::sprintf(logMsg, "Invalid input: %d", n);
        logger(logMsg);
        return -1;
    }
    if (n == 0) return 0;
    if (n == 1) return 1;

    long result = recursiveFib(n - 1, logger) + recursiveFib(n - 2, logger);

    std::sprintf(logMsg, "recursiveFib(%d) = %ld", n, result);
    logger(logMsg);

    addResult(n, result);

    return result;
}

void spinForever() {
    std::cout << "Entering infinite loop... (Press Ctrl+C in GDB)\n";
    long counter = 0;
    while (true) {
        counter++;
        if (counter % 5000000 == 0) {
            std::cout << "Spin counter: " << counter / 5000000 << "\n";
        }
    }
}

void cleanup() {
    if (gLogBuffer) {
        delete[] gLogBuffer;
        gLogBuffer = nullptr;
    }
    if (resultsArray) {
        delete[] resultsArray;
        resultsArray = nullptr;
    }
    resultsCount = 0;
    resultsCapacity = 0;
}

int main(int argc, char* argv[]) {
    int inputN = 10;

    if (argc > 1) {
        inputN = std::atoi(argv[1]);
    }

    initLogging();
    initResults();

    LogFuncT logger = SLogger;

    std::cout << "Computing Fibonacci(" << inputN << ")...\n";
    long result = recursiveFib(inputN, logger);

    std::cout << "Final Result: " << result << "\n";

    printResults();

    if (inputN > 30) {
        spinForever();
    }

    cleanup();

    return 0;
}