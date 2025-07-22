#include <iostream>
#include <cstdlib>      // for malloc, free
#include <malloc.h>     // for malloc_usable_size (glibc only)

int main() {
    int* p = new int[7]{1,2,3,4,5,6,7};

    // Works only with malloc_usable_size from glibc

    size_t actualSize = malloc_usable_size((p));
    std::cout << "Allocated size: " << actualSize << " bytes\n";

    //lets find allocated size of below block
    int* q{new int};
    size_t actualSize2 = malloc_usable_size((q));
    std::cout << "Allocated size: " << actualSize2 << " bytes\n";

    delete p;
    delete q;
    return 0;
}
