#include "../../inc/entities/TransactionLedger.hpp"

TransactionLedger::TransactionLedger(int capacity)
    : size(0), capacity(capacity), data(new Transaction*[capacity]) {}

TransactionLedger::TransactionLedger(const TransactionLedger& other)
    : size(other.size), capacity(other.capacity), data(new Transaction*[other.capacity]) {
    for (int i = 0; i < size; i++) {
        if (other.data[i] != nullptr) {
            data[i] = new Transaction(*(other.data[i]));
        } else {
            data[i] = nullptr;
        }
    }
}

TransactionLedger& TransactionLedger::operator=(const TransactionLedger& other) {
    if (this != &other) {
        for (int i = 0; i < size; i++) {
            delete data[i];
        }
        delete[] data;
        
        size = other.size;
        capacity = other.capacity;
        data = new Transaction*[capacity];
        
        for (int i = 0; i < size; i++) {
            if (other.data[i] != nullptr) {
                data[i] = new Transaction(*(other.data[i]));
            } else {
                data[i] = nullptr;
            }
        }
    }
    return *this;
}

TransactionLedger::~TransactionLedger() {
    for (int transactionIndex = 0; transactionIndex < size; transactionIndex++) {
        delete data[transactionIndex];
    }
    delete[] data;
}

void TransactionLedger::resize(int newCapacity) {
    Transaction** newData = new Transaction*[newCapacity];

    for (int transactionIndex = 0; transactionIndex < size; transactionIndex++) {
        newData[transactionIndex] = data[transactionIndex];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void TransactionLedger::add(Transaction* t) {
    if (size == capacity) {
        resize(capacity * 2);
    }

    data[size++] = t;
}

Transaction* TransactionLedger::operator[](int index) const {
    if (index < 0 || index >= size) {
        return nullptr;
    }
    return data[index];
}

int TransactionLedger::getSize() const {
    return size;
}

TransactionLedger TransactionLedger::getSubArray(const TransactionLedger& source, int startIndex, int count) {
    if (startIndex < 0 || count <= 0 || startIndex >= source.getSize()) {
        return TransactionLedger(0);
    }
    
    int actualCount = count > (source.getSize() - startIndex) ? (source.getSize() - startIndex) : count;
    if (actualCount <= 0) {
        return TransactionLedger(0);
    }
    
    TransactionLedger result(actualCount);

    for (int transactionIndex = 0; transactionIndex < actualCount; transactionIndex++) {
        if (startIndex + transactionIndex < source.getSize()) {
            result.add(new Transaction(*(source[startIndex + transactionIndex])));
        }
    }
    
    return result;
}

