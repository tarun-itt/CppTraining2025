#include <iostream>

int add(int a, int b) {
    return a + b;
}

void printArray(int* arr, int size) {
    for(int i = 0; i < size; ++i) {
        std::cout << *(arr + i) << " ";
    }
    std::cout << "\n";
}

int main() {
    int x = 10;
    int* p = &x;
    std::cout << *p << "\n";

    *p = 20;
    std::cout << x << "\n";

    int arr[5] = {1, 2, 3, 4, 5};
    int* parr = arr;
    printArray(parr, 5);

    parr++;
    std::cout << *parr << "\n";

    int* nullPtr = nullptr;
    if (nullPtr == nullptr) {
        std::cout << "nullPtr is nullptr\n";
    }

    int* danglingPtr;
    {
        int y = 50;
        danglingPtr = &y;
    }
    std::cout << *danglingPtr << "\n";

    int (*funcPtr)(int, int) = add;
    std::cout << funcPtr(5, 7) << "\n";

    return 0;
}
