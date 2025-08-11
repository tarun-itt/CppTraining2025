#ifndef USERDATABASEMANAGER_HPP
#define USERDATABASEMANAGER_HPP

#include <string>

#include "User.hpp"
#include "UserRegistry.hpp"

class UserDatabaseManager {
    public:
        friend class Admin;
        UserDatabaseManager();
        User* findUser(const std::string& email);
        User* findUser(uint32_t userId);
        void setAccountNumber(uint32_t userId, uint32_t accountNumber);
        
    private:
        uint32_t generateUserId();
        uint32_t addAdmin(const std::string& email, const std::string& password);
        uint32_t addAccountHolder(const std::string& email, const std::string& password);
        bool removeUser(const std::string& email);
        
        UserRegistry admins;
        UserRegistry accountHolders;
};

#endif
