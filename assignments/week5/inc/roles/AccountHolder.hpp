#ifndef ACCOUNTHOLDER_HPP
#define ACCOUNTHOLDER_HPP

#include <cstdint>
#include <string>

#include "../entities/User.hpp"

struct LoginResult;

class AccountHolder : public User {
    public:
        AccountHolder(const std::string& email, const std::string& password, uint32_t userId);
        
        uint32_t getAccountNumber() const;
        
        bool requestDeposit(const LoginResult& loginResult, double amount);
        bool requestWithdraw(const LoginResult& loginResult, double amount);
        
        friend class UserDatabaseManager;
        
    private:
        uint32_t accountNumber;
        void setAccountNumber(uint32_t accountNumber);
};

#endif