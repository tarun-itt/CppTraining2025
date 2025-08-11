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
            case MenuUtils::AdminMenuChoice::USER_MANAGEMENT: {
                showUserManagementMenu();
                break;
            }
            case MenuUtils::AdminMenuChoice::ACCOUNT_MANAGEMENT: {
                showAccountManagementMenu();
                break;
            }
            case MenuUtils::AdminMenuChoice::LOGOUT: {
                handleLogout();
                running = false;
                break;
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
    std::cout << "1. User Management\n";
    std::cout << "2. Account Management\n";
    std::cout << "3. Logout\n";
    std::cout << std::endl;
}

void AdminMenu::showUserManagementMenu() {
    MenuUtils::showHeader("USER MANAGEMENT");
    std::cout << "User Management Options:" << std::endl;
    std::cout << "1. Add New Admin\n";
    std::cout << "2. Add New Account Holder\n";
    std::cout << "3. Remove User\n";
    std::cout << "4. Back to Main Menu" << std::endl;
    std::cout << std::endl;
    
    int choice = MenuUtils::promptForChoice();
    
    switch (static_cast<MenuUtils::UserManagementChoice>(choice)) {
        case MenuUtils::UserManagementChoice::ADD_ADMIN: {
            showAddNewUserMenu(MenuUtils::UserType::ADMIN);
            break;
        }
        case MenuUtils::UserManagementChoice::ADD_ACCOUNT_HOLDER: {
            showAddNewUserMenu(MenuUtils::UserType::ACCOUNT_HOLDER);
            break;
        }
        case MenuUtils::UserManagementChoice::REMOVE_USER: {
            showRemoveUserMenu();
            break;
        }
        case MenuUtils::UserManagementChoice::BACK: {
            return;
        }
        default: {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    
   
}

void AdminMenu::showAccountManagementMenu() {
    MenuUtils::showHeader("ACCOUNT MANAGEMENT");
    std::cout << "Account Management Options:\n";
    std::cout << "1. Create New Account\n";
    std::cout << "2. Close Account\n";
    std::cout << "3. Back to Main Menu\n";
    std::cout << std::endl;
    
    int choice = MenuUtils::promptForChoice();
    
    switch (static_cast<MenuUtils::AccountManagementChoice>(choice)) {
        case MenuUtils::AccountManagementChoice::CREATE_ACCOUNT: {
            showCreateAccountMenu();
            break;
        }
        case MenuUtils::AccountManagementChoice::CLOSE_ACCOUNT: {
            showCloseAccountMenu();
            break;
        }
        case MenuUtils::AccountManagementChoice::BACK: {
            return;
        }
        default: {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

void AdminMenu::handleLogout() {
    authController.logout();
    MenuUtils::showSuccess("Logged out successfully!\n");   
}

void AdminMenu::showAddNewUserMenu(MenuUtils::UserType userType) {
    std::string userTypeName = (userType == MenuUtils::UserType::ADMIN) ? "ADMIN" : "ACCOUNT HOLDER";
    MenuUtils::showHeader("ADD NEW " + userTypeName);
    
    std::string email = MenuUtils::promptForEmail();
    std::string password = MenuUtils::promptForPassword(true);
    
    if (!password.empty()) {
        Admin* admin = dynamic_cast<Admin*>(loginResult.user);
        if (admin) {
           uint32_t userId = (userType == MenuUtils::UserType::ADMIN) ? 
                admin->requestAddAdmin(userManager, email, password) :
                admin->requestAddAccountHolder(userManager, email, password);
            MenuUtils::showSuccess(userTypeName + " added successfully! User ID: " + std::to_string(userId) + "\n");
        }else {
            MenuUtils::showError("You are not authorized for this action. \n");
        }
    } else {
        MenuUtils::showError("Password setup failed.\n");
        return;
    }
}

void AdminMenu::showRemoveUserMenu() {
    MenuUtils::showHeader("REMOVE USER");
    std::string email = MenuUtils::promptForEmail();
    
    Admin* admin = dynamic_cast<Admin*>(loginResult.user);
    if (admin && admin->requestRemoveUser(userManager, email)) {
        MenuUtils::showSuccess("User removed successfully!");
    } else {
        MenuUtils::showError("Failed to remove user.");
    }
}

void AdminMenu::showCreateAccountMenu() {
    MenuUtils::showHeader("CREATE NEW ACCOUNT");
    uint32_t userId;
    userId = MenuUtils::promptForUserId();
    
    double initialDeposit = MenuUtils::promptForAmount();
    
    Admin* admin = dynamic_cast<Admin*>(loginResult.user);
    if (admin) {
        try {
            uint32_t accountNumber = admin->requestCreateAccount(loginResult, userManager, userId, initialDeposit);
            MenuUtils::showSuccess("Account created successfully! Account Number: " + std::to_string(accountNumber));
        } catch (const std::runtime_error& e) {
            MenuUtils::showError(e.what());
        }
    }else {
        MenuUtils::showError("You are not authorized to create an account.");
    }
}

void AdminMenu::showCloseAccountMenu() {
    MenuUtils::showHeader("CLOSE ACCOUNT");
    uint32_t accountNumber;
    uint32_t userId = MenuUtils::promptForUserId();
    accountNumber = dynamic_cast<AccountHolder*>(userManager.findUser(userId))->getAccountNumber();

    Admin* admin = dynamic_cast<Admin*>(loginResult.user);
    if (admin) {
        try {
            if (admin->requestCloseAccount(loginResult, accountNumber)) {
                MenuUtils::showSuccess("Account closed successfully!");
            } else {
                MenuUtils::showError("Failed to close account.");
            }
        } catch (const std::runtime_error& e) {
            MenuUtils::showError(e.what());
        }
    }else {
        MenuUtils::showError("You are not authorized to close an account.");
    }
} 