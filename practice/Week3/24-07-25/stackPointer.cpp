#include <iostream>

int main() {
    void* stack_ptr = nullptr;

    asm("mov %%rsp, %0" : "=r"(stack_ptr));

    std::cout << "Current stack pointer (rsp): " << stack_ptr << std::endl;
    return 0;
}
