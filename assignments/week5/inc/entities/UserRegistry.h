#ifndef UserRegistry_HPP
#define UserRegistry_HPP

#include <cstdint>

#include "../../inc/entities/User.h"
#include "../../inc/interfaces/IUser.h"

class UserRegistry {
private:
    IUser** data;
    uint32_t size;
    int capacity;

    void resize(int newCapacity);

public:
    explicit UserRegistry(int capacity = 10);
    ~UserRegistry();

    void add(IUser* a);
    IUser* operator[](int index) const;
    int getSize() const;

    bool remove(const std::string& email);
};

#endif