#include "../../inc/entities/TransactionLedger.hpp"

TransactionLedger::TransactionLedger(int capacity)
    : size(0), capacity(capacity), data(new Transaction*[capacity]) {}

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
    return data[index];
}

int TransactionLedger::getSize() const {
    return size;
}

TransactionLedger TransactionLedger::getSubArray(const TransactionLedger& source, int startIndex, int count) {
    TransactionLedger result(count > 10 ? count : 10);

    for (int transactionIndex = 0; transactionIndex < count; transactionIndex++) {
        result.add(new Transaction(*source[startIndex + transactionIndex]));
    }
    
    return result;
}

