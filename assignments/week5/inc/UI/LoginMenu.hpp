#ifndef LOGINMENU_HPP
#define LOGINMENU_HPP

#include <string>

#include "MenuUtils.hpp"
#include "../auth/AuthController.hpp"
#include "../auth/LoginResult.hpp"

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