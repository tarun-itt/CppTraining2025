#include <iostream>

int* makeArray() {
    int* a = new int[3];
    a[0] = 10; a[1] = 20; a[2] = 30;
    return a;
}

int main() {
    int* p = makeArray();
    delete p;
    std::cout << "deleted p\n";

    int *q = new int[100];
    q[0] = 1;               

    std::cout << "q[0] = " << q[0] << "\n";
    delete[] q;
    return 0;
}
