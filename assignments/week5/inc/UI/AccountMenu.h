#ifndef ACCOUNTMENU_HPP
#define ACCOUNTMENU_HPP

#include <string>

#include "MenuUtils.h"
#include "../auth/AuthController.h"
#include "../auth/LoginResult.h"

class AccountMenu {
    public:
        AccountMenu(AuthController& authController, LoginResult& loginResult);
        ~AccountMenu();
        
        void run();
        
    private:
        AuthController& authController;
        LoginResult& loginResult;
        
        void showMainMenu();
        void showTransactionMenu();
        void printMiniStatement();
        void printFullStatement();
        void showAccountInfo();
        void handleLogout();
        void showTransactionMenu(TransactionType type);
};

#endif 