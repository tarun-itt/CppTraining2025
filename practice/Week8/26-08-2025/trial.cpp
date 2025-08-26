#include <iostream>

template <typename T>
T add(const T& a, const T& b) {
    return a + b;
}



template<typename T>
T multiply(T a, T b) { return a * b; }

int main() {
    int intResult = add<int>(5, 3);
    std::cout << "Adding integers: 5 + 3 = " << intResult << std::endl;
    
    double doubleResult = add<double>(2.5, 3.7);
    std::cout << "Adding doubles: 2.5 + 3.7 = " << doubleResult << std::endl;
    
    auto intResult2 = add(10, 20);
    auto doubleResult2 = add(1.1, 2.2);
    
    std::cout << "Auto-deduced int: " << intResult2 << std::endl;
    std::cout << "Auto-deduced double: " << doubleResult2 << std::endl;
    
    auto result3 = multiply<int>(5, 3.2);
    std::cout<<result3;

    return 0;
}