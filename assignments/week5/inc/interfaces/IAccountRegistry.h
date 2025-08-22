#ifndef IACCOUNTREGISTRY_H
#define IACCOUNTREGISTRY_H

#include <cstdint>
#include "../entities/Account.hpp"

class IAccountRegistry {
public:
    virtual ~IAccountRegistry() = default;
    
    virtual void add(Account* a) = 0;
    virtual Account* operator[](int index) const = 0;
    virtual int getSize() const = 0;
    virtual bool remove(int accountId) = 0;
};

#endif 