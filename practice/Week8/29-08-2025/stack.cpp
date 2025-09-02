#include <exception>
#include <iostream>
#include <stdexcept>

template<typename T>
class Stack {
    T* data;
    int capacity;
    int topPtr;

public:
    Stack(int capacity=10):capacity(capacity), topPtr(-1), data(new T[capacity]){}
    ~Stack() {
        delete[] data;
    }

    bool push(const T& value){
        if(topPtr < capacity - 1){
            data[++topPtr] = value;
            return true;
        } else {
            return false;
        }
    }

    bool pop(const T& value){
        if(topPtr < 0) return false;
        value = data[topPtr--];
        return true;
    }

    T top(const T& value) const {
        if(topPtr < 0) {
            throw std::runtime_error("Stack Underflow");
        }
        value = data[topPtr];
        return true;
    }

    bool empty() const {
        return topPtr == -1;
    }
};

int main() {
    Stack<int> s;
    int x;
    s.push(10);
    s.push(20);

    return 0;
}
