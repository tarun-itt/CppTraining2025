#ifndef ADMINMENU_HPP
#define ADMINMENU_HPP

#include <string>

#include "MenuUtils.h"
#include "../auth/AuthController.h"
#include "../auth/LoginResult.h"
#include "../entities/UserDatabaseManager.h"

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