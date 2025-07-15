#include <iostream>

int main() {
    int val = 3;
    switch (val) {
        case 0:
            std::cout << "Zero\n";
            break;
        case 1:
            std::cout << "One\n";
            break;
        case 2:
            std::cout << "Two\n";
            break;
        case 3:
            std::cout << "Three\n";
            break;
        case 4:
            std::cout << "Four\n";
            break;
        case 5:
            std::cout << "Five\n";
            break;
        default:
            std::cout << "Other\n";
            break;
    }
    return 0;
}
