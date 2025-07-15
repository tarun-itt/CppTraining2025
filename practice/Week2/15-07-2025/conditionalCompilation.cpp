#include <iostream>

#ifdef _WIN32
    #define PLATFORM_NAME "Windows"
#elif __APPLE__
    #define PLATFORM_NAME "macOS"
#elif __linux__
    #define PLATFORM_NAME "Linux"
#else
    #define PLATFORM_NAME "Unknown OS"
#endif

//#define DEBUG_MODE

int main(){


std::cout << "Compiled for: " << PLATFORM_NAME;

std::cout<<"\n\n";

#ifdef DEBUG_MODE
std::cout<<"Log for debug mode, comment the define DEBUG_MODE";

#else

std::cout<<"Normal mode";
#endif
return 0;
}
