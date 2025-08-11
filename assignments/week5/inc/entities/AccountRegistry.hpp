#ifndef AccountRegistry_HPP
#define AccountRegistry_HPP

#include <cstdint>

#include "../../inc/entities/Account.hpp"

class AccountRegistry {
private:
    Account** data;
    uint32_t size;
    int capacity;

    void resize(int newCapacity);

public:
    explicit AccountRegistry(int capacity = 10);
    ~AccountRegistry();

    void add(Account* a);
    Account* operator[](int index) const;
    int getSize() const;

    bool remove(int accountId);
};

#endif
