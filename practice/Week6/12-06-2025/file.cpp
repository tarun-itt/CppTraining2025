#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("trialText.txt");

    if (!file) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    file.close();
    return 0;
}
