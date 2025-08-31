#ifndef LOGINMENU_HPP
#define LOGINMENU_HPP

#include <string>

#include "MenuUtils.h"
#include "../auth/AuthController.h"
#include "../auth/LoginResult.h"

class LoginMenu {
    public:
        LoginMenu(AuthController& authController);
        ~LoginMenu();
        
        LoginResult run();
        
    private:
        AuthController& authController;
        
        void showMainMenu();
        void showLoginForm();
        LoginResult performLogin();
};

#endif 