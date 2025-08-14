#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <cstdint>
#include <string>

#include "../entities/User.hpp"
#include "../entities/UserDatabaseManager.hpp"

struct LoginResult;

class Admin : public User {
    public:
        Admin(const std::string& email, const std::string& password, uint32_t userId);
        
        uint32_t requestAddAdmin(UserDatabaseManager& userManager, const std::string& email, const std::string& password);
        uint32_t requestAddAccountHolder(LoginResult& loginResult, UserDatabaseManager& userManager, const std::string& email, const std::string& password, double initialDeposit);
        bool requestRemoveUser(LoginResult& loginResult, UserDatabaseManager& userManager, const std::string& email);

    private:
        uint32_t requestCreateAccount(const LoginResult& loginResult, UserDatabaseManager& userManager, uint32_t userId, double initialDeposit);
        bool requestCloseAccount(const LoginResult& loginResult, uint32_t accountNumber);
};

#endif