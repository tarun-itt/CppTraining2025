#include "../inc/table.h"

Table::Table() : size(0), maxCapacity(0), rows(nullptr) {}

Table::Table(int capacity)
    : size(0), maxCapacity(capacity), rows(new Row[capacity]) {}

Table::Table(const Table& other)
    : size(other.size), maxCapacity(other.maxCapacity), rows(new Row[other.maxCapacity]) {
    for (int row = 0; row < size; row++) {
        rows[row] = other.rows[row];
    }
}

Table& Table::operator=(const Table& other) {
    if (this != &other) {
        if (rows != nullptr) {
            delete[] rows;
        }
        
        size = other.size;
        maxCapacity = other.maxCapacity;
        rows = new Row[maxCapacity];
        
        for (int row = 0; row < size; row++) {
            rows[row] = other.rows[row];
        }
    }
    return *this;
}

Table::~Table() {
    if (rows != nullptr) {
        delete[] rows;
    }
}

void Table::resize(int newCapacity) {
    Row* newRows = new Row[newCapacity];

    for (int row = 0; row < size; row++) {
        newRows[row] = rows[row];
    }

    delete[] rows;
    rows = newRows;
    maxCapacity = newCapacity;
}

void Table::add(const Row& row) {
    if (size == maxCapacity) {
        resize(maxCapacity * 2);
    }

    rows[size++] = row;
}

Row& Table::operator[](int index) {
    return rows[index];
}

const Row& Table::operator[](int index) const {
    return rows[index];
} 