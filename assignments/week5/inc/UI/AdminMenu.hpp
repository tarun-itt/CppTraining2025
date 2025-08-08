#ifndef ADMINMENU_HPP
#define ADMINMENU_HPP

#include "../auth/AuthController.hpp"
#include "../auth/LoginResult.hpp"
#include "../entitites/UserDatabaseManager.hpp"
#include "MenuUtils.hpp"
#include <string>

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
        void addNewAdmin();
        void addNewAccountHolder();
        void removeUser();
        void createAccount();
        void closeAccount();
};

#endif 