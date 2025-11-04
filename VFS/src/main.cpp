#include <iostream>

#include "Application.h"

int main(int argc, char* argv[]) {
    std::string filename = "vfs_data.txt";
    
    if (argc > 1) {
        filename = argv[1];
        std::cout << "Using data file: " << filename << std::endl;
    } else {
        std::cout << "Using default data file: " << filename << std::endl;
    }
    
    Application app(filename);
    app.run();
    return 0;
}