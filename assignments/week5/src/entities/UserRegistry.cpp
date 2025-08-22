#include "../../inc/entities/UserRegistry.hpp"

UserRegistry::UserRegistry(int capacity)
    : size(0), capacity(capacity), data(new IUser*[capacity]) {}

UserRegistry::~UserRegistry() {
    for (int userIndex = 0; userIndex < size; userIndex++) {
        delete data[userIndex];
    }
    delete[] data;
}

void UserRegistry::resize(int newCapacity) {
    IUser** newData = new IUser*[newCapacity];
    for (int userIndex = 0; userIndex < size; userIndex++) {
        newData[userIndex] = data[userIndex];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void UserRegistry::add(IUser* a) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = a;
}

IUser* UserRegistry::operator[](int index) const {
    return data[index];
}

int UserRegistry::getSize() const {
    return size;
}

bool UserRegistry::remove(const std::string& email) {
    for (int userIndex = 0; userIndex < size; userIndex++) {
        if (data[userIndex]->getEmail() == email) {
            delete data[userIndex];

            for (int innerUserIndex = userIndex; innerUserIndex + 1 < size; innerUserIndex++) {
                data[innerUserIndex] = data[innerUserIndex + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}
