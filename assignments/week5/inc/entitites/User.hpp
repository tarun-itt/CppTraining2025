#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "TransactionArray.hpp"

struct LoginResult;

class User {
    public:
        std::string getEmail() const;
        std::string getPassword() const;

        virtual uint32_t getUserId() const; 
        virtual double requestBalance(const LoginResult& loginResult, uint32_t accountNumber);
        virtual TransactionArray requestMiniStatement(const LoginResult& loginResult, uint32_t accountNumber);
        virtual TransactionArray requestRangeStatement(const LoginResult& loginResult, uint32_t accountNumber, std::string startDate, std::string endDate);

        friend class UserDatabaseManager;
        
    protected:
        User(const std::string& email, const std::string& password);

        std::string email;
        std::string password;
        uint32_t userId;
};

#endif