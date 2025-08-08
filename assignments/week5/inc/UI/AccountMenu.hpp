#ifndef ACCOUNTMENU_HPP
#define ACCOUNTMENU_HPP

#include "../auth/AuthController.hpp"
#include "../auth/LoginResult.hpp"
#include "MenuUtils.hpp"
#include <string>

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
        void showAccountInfo();
        void handleLogout();
        void performDeposit();
        void performWithdraw();
};

#endif 