#include <iostream>
#include <limits>

#include "../../inc/UI/LoginMenu.hpp"

LoginMenu::LoginMenu(AuthController& authController): authController(authController) {}

LoginMenu::~LoginMenu() {}

void LoginMenu::showMainMenu() {
    MenuUtils::showHeader("BANKING SYSTEM");
    std::cout << "1. Login\n";
    std::cout << "2. Exit\n";
    std::cout << std::endl;
}

LoginResult LoginMenu::run() {
    bool running = true;
    LoginResult result{nullptr, nullptr, ""};

    while (running) {
        showMainMenu();
        int choice = MenuUtils::promptForChoice();

        switch (static_cast<MenuUtils::MainMenuChoice>(choice)) {
            case MenuUtils::MainMenuChoice::LOGIN:{
                result = performLogin();
                if (result.user != nullptr && result.bank != nullptr) {
                    running = false;
                }
                break;
            }
            case MenuUtils::MainMenuChoice::EXIT:{
                running = false;
                std::cout << "\nBye...\n";
                break;
            }
            default:{
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
    
    return result;
}

LoginResult LoginMenu::performLogin() {
    std::string email = MenuUtils::promptForEmail();
    std::string password = MenuUtils::promptForPassword();
    
    LoginResult result = authController.login(email, password);
    
    if (result.user != nullptr && result.bank != nullptr) {
        MenuUtils::showSuccess("Login successful!\n");
    } else {
        MenuUtils::showError("Login failed. Please check your credentials.\n");
        result = LoginResult{nullptr, nullptr, ""};
    }
    return result;
} 