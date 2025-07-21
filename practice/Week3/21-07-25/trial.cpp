#include <iostream>
int& getRef(){
    int* ptr = new int(5);
    int& ref = *ptr;
    return *ptr;
}

#include <iostream>

struct S {
    int ref; 

};

int main() {
    int x = 42;
    int& r = x;

    std::cout << "Size of int x: " << sizeof(x) << " bytes\n";
    std::cout << "Size of reference r: " << sizeof(r) << " bytes (same as int)\n";

    S s;
    std::cout << "Size of struct S (with int& member): " << sizeof(s) << " bytes\n";

    return 0;
}

