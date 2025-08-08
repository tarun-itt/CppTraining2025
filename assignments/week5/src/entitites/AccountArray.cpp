#include "../../inc/entitites/AccountArray.hpp"

AccountArray::AccountArray(int capacity)
    : size(0), capacity(capacity), data(new Account*[capacity]) {}

AccountArray::~AccountArray() {
    for (int accountIndex = 0; accountIndex < size; accountIndex++) {
        delete data[accountIndex];
    }
    delete[] data;
}

void AccountArray::resize(int newCapacity) {
    Account** newData = new Account*[newCapacity];
    for (int accountIndex = 0; accountIndex < size; accountIndex++) {
        newData[accountIndex] = data[accountIndex];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void AccountArray::add(Account* a) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = a;
}

Account* AccountArray::operator[](int index) const {
    return data[index];
}

int AccountArray::getSize() const {
    return size;
}

bool AccountArray::remove(int accountId) {
    for (int accountIndex = 0; accountIndex < size; accountIndex++) {
        if (data[accountIndex]->getAccountNumber() == accountId) {
            delete data[accountIndex];

            for (int innerAccountIndex = accountIndex; innerAccountIndex + 1 < size; innerAccountIndex++) {
                data[innerAccountIndex] = data[innerAccountIndex + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}
