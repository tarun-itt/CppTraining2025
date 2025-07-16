#include <iostream>

#define PI 3.1459
#define SQUARE(radius) ((radius)*(radius))
#define MULTIPLY(a,b) ((a)*(b))

//multi line definition
#define LOG(msg) std::cout<<"[LOG] "<<msg<<"\n"; \
                std::cout<<"[INFO] Time: "<<__TIME__<<"\n";

//using macro as a flag for conditional compilation, for example when debugging
#define DEBUG 1

#define CONCAT(x,y) x##y

void circleArea(int radius){
    std::cout<<"Area of circle: "<<(PI * radius * radius)<<" units\n";
}

void circleArea2(int radius){
    std::cout<<"Area of circle2: "<<(PI * SQUARE(radius+1))<<" units\n";
}
int main(){
    circleArea(5);
    circleArea2(3);

    #if defined(DEBUG)
    LOG("=== RUNNING IN DEBUG MODE ===")
    #endif

    #if DEBUG == 0
    LOG("USING DEVELOPMENT MODE")
    #elif DEBUG == 1
    LOG("USING PROD MODE")
    #endif

    #if MULTIPLY(4,8) == 32
        std::cout<<"INSIDE MULTIPLY!\n";
        #if 1
            std::cout<<"INSIDE MULTIPLY -> IF\n";
        #endif
    #endif
    
    std::cout<<"\n\n\n";
    int helloWorld = 2;
    std::cout<<CONCAT(hello,World);
    return 0;
}