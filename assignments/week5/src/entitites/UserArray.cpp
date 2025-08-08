#include "../../inc/entitites/UserArray.hpp"

UserArray::UserArray(int capacity)
    : size(0), capacity(capacity), data(new User*[capacity]) {}

UserArray::~UserArray() {
    for (int userIndex = 0; userIndex < size; userIndex++) {
        delete data[userIndex];
    }
    delete[] data;
}

void UserArray::resize(int newCapacity) {
    User** newData = new User*[newCapacity];
    for (int userIndex = 0; userIndex < size; userIndex++) {
        newData[userIndex] = data[userIndex];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void UserArray::add(User* a) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = a;
}

User* UserArray::operator[](int index) const {
    return data[index];
}

int UserArray::getSize() const {
    return size;
}

bool UserArray::remove(const std::string& email) {
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
