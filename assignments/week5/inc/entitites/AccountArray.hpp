#ifndef ACCOUNTARRAY_HPP
#define ACCOUNTARRAY_HPP

#include "../../inc/entitites/Account.hpp"
#include <cstdint>

class AccountArray {
private:
    Account** data;
    uint32_t size;
    int capacity;

    void resize(int newCapacity);

public:
    explicit AccountArray(int capacity = 10);
    ~AccountArray();

    void add(Account* a);
    Account* operator[](int index) const;
    int getSize() const;

    bool remove(int accountId);
};

#endif
