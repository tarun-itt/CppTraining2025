#include <iostream>
#include <stdexcept> 
#include <string>    

void processNumber(int num) {
    if (num <= 0) {
        throw std::invalid_argument("Number must be greater than zero!");
    }
    std::cout << "Processing number: " << num << std::endl;
}

int main() {
    try {
        int number;

        std::cout << "Enter a positive number: ";
        std::cin >> number;

        processNumber(number);
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred!" << std::endl;
    }

    return 0;
}
