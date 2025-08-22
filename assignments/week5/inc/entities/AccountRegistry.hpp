#ifndef AccountRegistry_HPP
#define AccountRegistry_HPP

#include <cstdint>
#include "../interfaces/IAccountRegistry.h"

class AccountRegistry : public IAccountRegistry {
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
