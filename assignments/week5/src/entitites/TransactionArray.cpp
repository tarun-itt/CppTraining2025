#include "../../inc/entitites/TransactionArray.hpp"

TransactionArray::TransactionArray(int capacity)
    : size(0), capacity(capacity), data(new Transaction*[capacity]) {}

TransactionArray::~TransactionArray() {
    for (int transactionIndex = 0; transactionIndex < size; transactionIndex++) {
        delete data[transactionIndex];
    }
    delete[] data;
}

void TransactionArray::resize(int newCapacity) {
    Transaction** newData = new Transaction*[newCapacity];

    for (int transactionIndex = 0; transactionIndex < size; transactionIndex++) {
        newData[transactionIndex] = data[transactionIndex];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void TransactionArray::add(Transaction* t) {
    if (size == capacity) {
        resize(capacity * 2);
    }

    data[size++] = t;
}

Transaction* TransactionArray::operator[](int index) const {
    return data[index];
}

int TransactionArray::getSize() const {
    return size;
}

TransactionArray TransactionArray::getSubArray(const TransactionArray& source, int startIndex, int count) {
    TransactionArray result(count > 10 ? count : 10);

    for (int transactionIndex = 0; transactionIndex < count; transactionIndex++) {
        result.add(new Transaction(*source[startIndex + transactionIndex]));
    }
    
    return result;
}

