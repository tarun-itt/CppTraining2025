#include <thread>
#include <functional>
#include <iostream>

void myFunc(int &x) {
    x += 10;
}

int main() {
    int a = 5;
    std::thread t(myFunc, std::ref(a));
    //join();
    t.detach();
    std::cout<<"A: "<<a;

    return 0;
}
