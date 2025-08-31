#ifndef IACCOUNTHOLDER_H
#define IACCOUNTHOLDER_H

#include <cstdint>
#include <string>

#include "IUser.h"

struct LoginResult;

class IAccountHolder{
public:
    virtual ~IAccountHolder() = default;
    
    virtual uint32_t getAccountNumber() const = 0;
    virtual bool requestDeposit(const LoginResult& loginResult, double amount) = 0;
    virtual bool requestWithdraw(const LoginResult& loginResult, double amount) = 0;
};

#endif 