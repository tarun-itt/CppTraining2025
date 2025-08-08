#ifndef AUTHCONTROLLER_HPP
#define AUTHCONTROLLER_HPP

#include "LoginResult.hpp"
#include "../entitites/User.hpp"
#include "../entitites/UserDatabaseManager.hpp"

#include <string>

class AuthController {
    public:
        AuthController(UserDatabaseManager& userManager);
        
        LoginResult login(const std::string& email, const std::string& password);
        bool logout();
        User* getCurrentUser();
        bool isAdminLoggedIn();
        
    private:
        User* currentUser;
        bool isLoggedIn;
        UserDatabaseManager& userManager;

        bool validateToken(std::string sessionToken);
};

#endif