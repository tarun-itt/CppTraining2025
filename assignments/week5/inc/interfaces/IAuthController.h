#ifndef IAUTHCONTROLLER_HPP
#define IAUTHCONTROLLER_HPP

#include <string>

#include "../interfaces/IBank.h"

struct LoginResult;
class IUser;

class IAuthController {
public:
    virtual ~IAuthController() = default;
    
    virtual LoginResult login(const std::string& email, const std::string& password) = 0;
    virtual bool logout() = 0;
    virtual IUser* getCurrentUser() = 0;
    virtual bool isAdminLoggedIn() = 0;
    virtual bool isEmailValid(const std::string& email) = 0;
};

#endif 