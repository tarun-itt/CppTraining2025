#ifndef USER_HPP
#define USER_HPP

#include <cstdint>
#include <string>

#include "TransactionLedger.hpp"

struct LoginResult;

class User {
    public:
        std::string getEmail() const;
        std::string getPassword() const;

        virtual uint32_t getUserId() const; 
        virtual double requestBalance(const LoginResult& loginResult, uint32_t accountNumber);
        virtual TransactionLedger requestMiniStatement(const LoginResult& loginResult, uint32_t accountNumber);
        virtual TransactionLedger requestRangeStatement(const LoginResult& loginResult, uint32_t accountNumber, std::string startDate, std::string endDate);
        
    protected:
        User(const std::string& email, const std::string& password, const uint32_t userId);

        std::string email;
        std::string password;
        uint32_t userId;
};

#endif