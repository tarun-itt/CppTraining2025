#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "../entitites/User.hpp"
#include "../entitites/UserDatabaseManager.hpp"

#include <string>

struct LoginResult;

class Admin : public User {
    public:
        Admin(const std::string& email, const std::string& password);
        
        bool requestAddAdmin(UserDatabaseManager& userManager, const std::string& email, const std::string& password);
        bool requestAddAccountHolder(UserDatabaseManager& userManager, const std::string& email, const std::string& password);
        bool requestRemoveUser(UserDatabaseManager& userManager, const std::string& email);
        uint32_t requestCreateAccount(const LoginResult& loginResult, uint32_t userId, double initialDeposit);
        bool requestCloseAccount(const LoginResult& loginResult, const std::string& accountNumber);
};

#endif