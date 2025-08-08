#ifndef LOGINMENU_HPP
#define LOGINMENU_HPP

#include "../auth/AuthController.hpp"
#include "../auth/LoginResult.hpp"
#include "MenuUtils.hpp"
#include <string>

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