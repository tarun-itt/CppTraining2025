#include <iostream>
#include <fstream>
#include <vector>
#include <csignal>
#include <string>

std::vector<std::string> buffer;
const std::string filename = "output.txt";

void handleSignal(int sig) {
    std::cerr << "\n Caught signal " << sig << ". Saving current state...\n";

    std::ofstream out(filename);
    if (out.is_open()) {
        for (const auto& line : buffer) {
            out << line << "\n";
        }
        out.close();
        std::cerr << "File saved to " << filename << "\n";
    } else {
        std::cerr << "Failed to save file!\n";
    }

    std::_Exit(1);
}

// so in this program i try to handle a signal, which i will send from outside to this progrma using shell, 
// and demonstrate more use case of handling signals, like saving state of program in case an interrupt like this happen
// but this is not the case if signals arises due to errors like SIGSEGV, these signals means the memory may be in corrupted state
int main() {
    std::signal(SIGINT, handleSignal);

    std::cout << "Program started (PID: " << getpid() << ").\n";
    std::cout << "Enter 10 lines of input. Send SIGINT/SIGTERM anytime to force save.\n";

    std::string line;
    for (int i = 0; i < 10; i++) {
        std::cout << "Input " << i+1 << ": ";
        if (!std::getline(std::cin, line)) break;
        buffer.push_back(line);
    }

    std::ofstream out(filename);
    if (out.is_open()) {
        for (const auto& line : buffer) {
            out << line << "\n";
        }
        out.close();
        std::cout << "All input saved to " << filename << "\n";
    }

    return 0;
}
