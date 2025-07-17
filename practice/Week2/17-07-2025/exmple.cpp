#include <iostream>

void f1() {
    static int x = 10;  
    int y = 5;          
    x++;
    std::cout << "x in f1: " << x << ", y in f1: " << y << std::endl;
}

static void f2() {
    static int x =34;
    int z = 15;         
    x++;
    std::cout << "x in f2: " << x << ", z in f2: " << z << std::endl;
}

//run this function using rm -c <filename>, to see static variables are stored in special .data .bss sotrage

int main() {
    f1();
    f2();
    
    return 0;
}
