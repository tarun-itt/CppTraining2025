#ifndef USERDATABASEMANAGER_HPP
#define USERDATABASEMANAGER_HPP

#include "User.hpp"
#include "UserArray.hpp"

#include <string>

class UserDatabaseManager {
    public:
        friend class Admin;
        UserDatabaseManager();
        User* findUser(const std::string& email);
        
    private:
        bool addAdmin(const std::string& email, const std::string& password);
        bool addAccountHolder(const std::string& email, const std::string& password);
        bool removeUser(const std::string& email);
        
        UserArray admins;
        UserArray accountHolders;
};

#endif
