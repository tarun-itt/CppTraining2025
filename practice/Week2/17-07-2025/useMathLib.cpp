#include <iostream>
#include "mathlib.h"

int main() {
    int num = 5;
    int num2 = 8;
    std::cout << "Square of " << num << " is " << square(num) << std::endl;
    std::cout << "Sum of " << num << "and "<<num2<<" is " << sum(num, num2) << std::endl;
    return 0;
}
