#include <iostream>

int main(){
    int* ptr = new int(34);
    std::cout<<"INT: "<<*ptr<<"\n";
    delete ptr;
    std::cout<<"ptr deleted\n"; 
    std::cout<<"INT: "<<*ptr<<"\n";
    // delete ptr; //detects double free and program aborts
    // std::cout<<"ptr deleted again\n"; 
    // std::cout<<"INT: "<<*ptr<<"\n";

}