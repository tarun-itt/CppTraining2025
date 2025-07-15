#include <iostream>
#include <string>

int operator "" _km(unsigned long long distance){
    return distance;
}
int main(){
    int d = 12_km;
    std::cout<<d;
}