#include <iostream>

// normal enums
enum  Color:uint8_t {Red, Yellow, Green}; //can be assigned underlying int type as well
enum Fruit {Apple, Orange, Lemon};


//enum classes, scoped and typesafe
enum class LogLevel: uint32_t{
    Error,
    Warning,
    Info
};

int main(){
    int color = Red;
    
    LogLevel level = LogLevel::Error;

    if(level==LogLevel::Error){
        std::cout<<"Hello";
    }

    std::cout<<sizeof(Red)<<" "<<sizeof(Orange)<<std::endl; //checkking the sizes
    return 0;
}