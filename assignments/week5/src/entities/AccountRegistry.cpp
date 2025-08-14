#include "../../inc/entities/AccountRegistry.hpp"

AccountRegistry::AccountRegistry(int capacity)
    : size(0), capacity(capacity), data(new Account*[capacity]) {}

AccountRegistry::~AccountRegistry() {
    for (int accountIndex = 0; accountIndex < size; accountIndex++) {
        delete data[accountIndex];
    }
    delete[] data;
}

void AccountRegistry::resize(int newCapacity) {
    Account** newData = new Account*[newCapacity];
    for (int accountIndex = 0; accountIndex < size; accountIndex++) {
        newData[accountIndex] = data[accountIndex];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void AccountRegistry::add(Account* a) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = a;
}

Account* AccountRegistry::operator[](int index) const {
    return data[index];
}

int AccountRegistry::getSize() const {
    return size;
}

bool AccountRegistry::remove(int accountId) {
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
