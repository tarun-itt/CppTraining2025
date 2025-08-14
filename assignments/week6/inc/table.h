#ifndef TABLE_H
#define TABLE_H

#include "row.h"

class Table {
private:
    int size;
    int maxCapacity;
    Row* rows;
    
    void resize(int newCapacity);
    
public:
    Table();
    Table(int capacity);
    Table(const Table& other);
    ~Table();
    
    Table& operator=(const Table& other);
    
    void add(const Row& row);
    Row& operator[](int index);
    const Row& operator[](int index) const;
    int getSize() const { return size; }
};

#endif 