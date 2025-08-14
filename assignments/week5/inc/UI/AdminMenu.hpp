#ifndef ADMINMENU_HPP
#define ADMINMENU_HPP

#include <string>

#include "MenuUtils.hpp"
#include "../auth/AuthController.hpp"
#include "../auth/LoginResult.hpp"
#include "../entities/UserDatabaseManager.hpp"

class AdminMenu {
    public:
        AdminMenu(AuthController& authController, LoginResult& loginResult, UserDatabaseManager& userManager);
        ~AdminMenu();
        
        void run();
        
    private:
        AuthController& authController;
        LoginResult& loginResult;
        UserDatabaseManager& userManager;
        
        void showMainMenu();
        void showUserManagementMenu();
        void showAccountManagementMenu();
        void handleLogout();
        void showAddNewUserMenu(MenuUtils::UserType userType);
        void showRemoveUserMenu();
        void showCreateAccountMenu();
        void showCloseAccountMenu();
};

#endif 