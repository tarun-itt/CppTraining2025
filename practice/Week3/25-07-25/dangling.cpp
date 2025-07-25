#include <iostream>

int* fun() {
    int local = 100;
    return &local;
}

void assignNew(int** leak){ //we need to use double pointers to make changes to the actual pointer, or we can use reference
    *leak = new int[5]{1,2,3,4,5};
}
int main() {
    int* leak = new int(42);

    assignNew(&leak);

    std::cout<<"First element of arra: "<<leak[0]<<"\n";

    int* dangling = fun(); // this is dangling pointer because the returned pointer reference is out of scope now
    std::cout << "Dangling pointer value: " << *dangling << std::endl; //resulting in segmetation fault

    return 0;
}
