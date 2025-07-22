#include <iostream>

int main() {
    char string1[] = "Hello World";

    char* ptrStr1 = string1;      
    char* ptrStr2 = &string1[0];

    std::cout << &string1      << "   &string1 (type: char (*)[12])\n";
    std::cout << &string1[0]   << "   &string1[0] (type: char*)\n";
    std::cout << *ptrStr1       << "   ptrStr1 (char*)\n";
    std::cout << ptrStr2       << "   ptrStr2 (char*)\n";


    std::string str1 = "popsicle";
    char* p = &str1[0];

    std::cout<<*p<<std::endl;
}
