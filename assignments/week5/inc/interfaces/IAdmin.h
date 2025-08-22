#ifndef IADMIN_H
#define IADMIN_H

#include <cstdint>
#include <string>

#include "IUser.h"

struct LoginResult;
class UserDatabaseManager;

class IAdmin{
public:
    virtual ~IAdmin() = default;
    
    virtual uint32_t requestAddAdmin(UserDatabaseManager& userManager, const std::string& email, const std::string& password) = 0;
    virtual uint32_t requestAddAccountHolder(LoginResult& loginResult, UserDatabaseManager& userManager, const std::string& email, const std::string& password, double initialDeposit) = 0;
    virtual bool requestRemoveUser(LoginResult& loginResult, UserDatabaseManager& userManager, const std::string& email) = 0;
};

#endif
