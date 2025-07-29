#include <iostream>

class DynamicArray {
  int *data;
  int size;

public:
  DynamicArray(int s) : size(s) {
    data = new int[size];
    std::cout << "Constructor: Array of size " << size << " allocated.\n";
  }

  ~DynamicArray() {
    delete[] data;
    std::cout << "Destructor Called: Array memory freed.\n";
  }
};

int main() {

  DynamicArray arr(5);

  return 0;
}
