#ifndef IUSER_HPP
#define IUSER_HPP

#include <cstdint>
#include <string>
#include "../entities/TransactionLedger.h"

struct LoginResult;

class IUser {
public:
    virtual ~IUser() = default;
    
    virtual std::string getEmail() const = 0;
    virtual std::string getPassword() const = 0;
    virtual uint32_t getUserId() const = 0;
    virtual double requestBalance(const LoginResult& loginResult, uint32_t accountNumber) = 0;
    virtual TransactionLedger requestMiniStatement(const LoginResult& loginResult, uint32_t accountNumber) = 0;
    virtual TransactionLedger requestStatementInDateRange(const LoginResult& loginResult, uint32_t accountNumber, std::string startDate, std::string endDate) = 0;
};

#endif 