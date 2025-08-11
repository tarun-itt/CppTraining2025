#ifndef UserRegistry_HPP
#define UserRegistry_HPP

#include <cstdint>

#include "../../inc/entities/User.hpp"

class UserRegistry {
private:
    User** data;
    uint32_t size;
    int capacity;

    void resize(int newCapacity);

public:
    explicit UserRegistry(int capacity = 10);
    ~UserRegistry();

    void add(User* a);
    User* operator[](int index) const;
    int getSize() const;

    bool remove(const std::string& email);
};

#endif