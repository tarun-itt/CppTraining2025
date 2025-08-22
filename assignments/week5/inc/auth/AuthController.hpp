#ifndef AUTHCONTROLLER_HPP
#define AUTHCONTROLLER_HPP

#include <string>

#include "LoginResult.hpp"
#include "../entities/User.hpp"
#include "../entities/UserDatabaseManager.hpp"
#include "../interfaces/IAuthController.h"
#include "../interfaces/IUser.h"

class AuthController {
    public:
        AuthController(UserDatabaseManager& userManager);
        
        LoginResult login(const std::string& email, const std::string& password);
        bool logout();
        IUser* getCurrentUser();
        bool isAdminLoggedIn();
        bool isEmailValid(const std::string& email);
        
    private:
        IUser* currentUser;
        bool isLoggedIn;
        UserDatabaseManager& userManager;

        bool validateToken(std::string sessionToken);
};

#endif