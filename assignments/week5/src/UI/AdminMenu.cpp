#include <iostream>
#include <limits>

#include "../../inc/UI/AdminMenu.hpp"
#include "../../inc/roles/Admin.hpp"
#include "../../inc/roles/AccountHolder.hpp"

AdminMenu::AdminMenu(AuthController& authController, LoginResult& loginResult, UserDatabaseManager& userManager)
    : authController(authController), loginResult(loginResult), userManager(userManager) {
}

AdminMenu::~AdminMenu() {
}

void AdminMenu::run() {
    bool running = true;
    
    while (running) {
        showMainMenu();
        int choice = MenuUtils::promptForChoice();
    
        switch (static_cast<MenuUtils::AdminMenuChoice>(choice)) {
            case MenuUtils::AdminMenuChoice::ADD_ADMIN: {
                showAddNewUserMenu(MenuUtils::UserType::ADMIN);
                break;
            }
            case MenuUtils::AdminMenuChoice::ADD_ACCOUNT_HOLDER: {
                showAddNewUserMenu(MenuUtils::UserType::ACCOUNT_HOLDER);
                break;
            }
            case MenuUtils::AdminMenuChoice::REMOVE_USER: {
                showRemoveUserMenu();
                break;
            }
            case MenuUtils::AdminMenuChoice::LOGOUT: {
                return;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
}

void AdminMenu::showMainMenu() {
    MenuUtils::showHeader("ADMIN Menu");
    std::cout << std::endl;
    std::cout << "1. Add New Admin\n";
    std::cout << "2. Add New Account Holder\n";
    std::cout << "3. Remove User\n";
    std::cout << "4. Logout\n" << std::endl;
    std::cout << std::endl;
}

void AdminMenu::handleLogout() {
    authController.logout();
    MenuUtils::showSuccess("Logged out successfully!\n");   
}

void AdminMenu::showAddNewUserMenu(MenuUtils::UserType userType) {
    std::string userTypeName = (userType == MenuUtils::UserType::ADMIN) ? "ADMIN" : "ACCOUNT HOLDER";
    MenuUtils::showHeader("ADD NEW " + userTypeName);
    
    try {
        std::string email = MenuUtils::promptForEmail();
        std::string password = MenuUtils::promptForPassword(true);
        
        if (!password.empty()) {
            Admin* admin = dynamic_cast<Admin*>(loginResult.user);
            if (admin) {
                uint32_t userId = (userType == MenuUtils::UserType::ADMIN) ? admin->requestAddAdmin(userManager, email, password) : admin->requestAddAccountHolder(loginResult, userManager, email, password, MenuUtils::promptForAmount("Initial Deposit: "));
                MenuUtils::showSuccess(userTypeName + " added successfully! User ID: " + std::to_string(userId) + "\n");
            }else {
                MenuUtils::showError("You are not authorized for this action. \n");
            }
        } else {
            MenuUtils::showError("Password setup failed.\n");
            return;
        }
    } catch (const std::invalid_argument& e) {
        MenuUtils::showError(e.what());
        return;
    }
}

void AdminMenu::showRemoveUserMenu() {
    MenuUtils::showHeader("REMOVE USER");
    try {
        std::string email = MenuUtils::promptForEmail();

        Admin* admin = dynamic_cast<Admin*>(loginResult.user);
        if (admin && admin->requestRemoveUser(loginResult, userManager, email)) {
        MenuUtils::showSuccess("User removed successfully!");
        } else {
            MenuUtils::showError("Failed to remove user.");
        }
    } catch (const std::invalid_argument& e) {
        MenuUtils::showError(e.what());
        return;
    }
}