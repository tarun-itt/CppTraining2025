#include <iostream>
#include <chrono>

#include <iostream>

// simulating as if a function were called on heap (though the function itself is currently running on stack)
struct HeapFunctionCall {
    HeapFunctionCall* next = nullptr;
    HeapFunctionCall* prev = nullptr;
    int run(int n) {
        if (n <= 1) return 1;
            return n * run(n-1); 
    }
};


int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n-1); 
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    factorial(15); 

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Stack Function took " << duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    HeapFunctionCall* func = new HeapFunctionCall;
    func->run(10);
    delete func; 
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Heap Function took " << duration.count() << " ms\n";
    return 0;
}
