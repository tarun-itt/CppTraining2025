#include <iostream>

int main(){
    int a = 10;
    a = a++ + a++;
    std::cout<<"Value of a: "<<a<<"\n"; //prints 21

    ++a = 19;
    std::cout<<"Value of a after preincrement: "<<a<<"\n"; //possible

    //a++ = 85;  //not possible


}