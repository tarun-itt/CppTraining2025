#ifndef ROW_H
#define ROW_H

#include <string>

class Row {
private:
    int size;
    int maxCapacity;
    std::string* elements;
    
    void resize(int newCapacity);
    
public:
    Row();
    Row(int capacity);
    Row(const Row& other);
    ~Row();
    
    Row& operator=(const Row& other);
    
    void add(const std::string& item);
    std::string& operator[](int index);
    const std::string& operator[](int index) const;
    int getSize() const { return size; }
};

#endif 