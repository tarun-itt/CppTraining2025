#ifndef USERARRAY_HPP
#define USERARRAY_HPP

#include "../../inc/entitites/User.hpp"
#include <cstdint>

class UserArray {
private:
    User** data;
    uint32_t size;
    int capacity;

    void resize(int newCapacity);

public:
    explicit UserArray(int capacity = 10);
    ~UserArray();

    void add(User* a);
    User* operator[](int index) const;
    int getSize() const;

    bool remove(const std::string& email);
};

#endif