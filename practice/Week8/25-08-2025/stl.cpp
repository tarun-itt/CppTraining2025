#include <codecvt>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

template <typename T>
class Stack {
private:
    std::vector<T> elements;
public:
    void push(const T& item) {
        elements.push_back(item);
    }

    void pop() {
        if (elements.empty()) {
            std::cout << "Stack is empty!\n";
            return;
        }
        elements.pop_back();
    }

    T top() const {
        if (elements.empty()) {
            throw std::out_of_range("Stack is empty!");
        }
        return elements.back();
    }

    bool empty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

template<typename T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}


int main() {

    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    std::cout << "Top of intStack: " << intStack.top() << "\n";

    Stack<std::string> strStack;
    strStack.push("Helloworld");
    strStack.push("abcds");
    std::cout << "Top of strStack: " << strStack.top() << "\n";

    int a = 23;
    int b =98;
    swap(a,b);
    std::cout<<a<<"  "<<b;
    return 0;
}
