#include "../inc/Row.h"

Row::Row() : size(0), maxCapacity(0), elements(nullptr) {}

Row::Row(int capacity)
    : size(0), maxCapacity(capacity), elements(new std::string[capacity]) {}

Row::Row(const Row& other)
    : size(other.size), maxCapacity(other.maxCapacity), elements(new std::string[other.maxCapacity]) {
    for (int element = 0; element < size; element++) {
        elements[element] = other.elements[element];
    }
}

Row& Row::operator=(const Row& other) {
    if (this != &other) {
        if (elements != nullptr) {
            delete[] elements;
        }
        
        size = other.size;
        maxCapacity = other.maxCapacity;
        elements = new std::string[maxCapacity];
        
        for (int element = 0; element < size; element++) {
            elements[element] = other.elements[element];
        }
    }
    return *this;
}

Row::~Row() {
    if (elements != nullptr) {
        delete[] elements;
        elements = nullptr;
    }
}

void Row::resize(int newCapacity) {
    std::string* newElements = new std::string[newCapacity];

    for (int element = 0; element < size; element++) {
        newElements[element] = elements[element];
    }

    delete[] elements;
    elements = newElements;
    maxCapacity = newCapacity;
}

void Row::add(const std::string& item) {
    if (size == maxCapacity) {
        resize(maxCapacity * 2);
    }

    elements[size++] = item;
}

std::string& Row::operator[](int index) {
    return elements[index];
}

const std::string& Row::operator[](int index) const {
    return elements[index];
} 