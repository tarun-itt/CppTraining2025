#include "../../inc/UI/AdminMenu.hpp"
#include "../../inc/roles/Admin.hpp"
#include <iostream>
#include <limits>

AdminMenu::AdminMenu(AuthController& authController, LoginResult& loginResult, UserDatabaseManager& userManager)
    : authController(authController), loginResult(loginResult), userManager(userManager) {
}

AdminMenu::~AdminMenu() {
}

void AdminMenu::run() {
    bool running = true;
    
    while (running) {
        showMainMenu();
        int choice = MenuUtils::getChoice();
        
        switch (static_cast<MenuUtils::AdminMenuChoice>(choice)) {
            case MenuUtils::AdminMenuChoice::USER_MANAGEMENT:
                showUserManagementMenu();
                break;
            case MenuUtils::AdminMenuChoice::ACCOUNT_MANAGEMENT:
                showAccountManagementMenu();
                break;
            case MenuUtils::AdminMenuChoice::LOGOUT:
                handleLogout();
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
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
    
    int choice = MenuUtils::getChoice();
    
    switch (static_cast<MenuUtils::UserManagementChoice>(choice)) {
        case MenuUtils::UserManagementChoice::ADD_ADMIN:
            addNewAdmin();
            break;
        case MenuUtils::UserManagementChoice::ADD_ACCOUNT_HOLDER:
            addNewAccountHolder();
            break;
        case MenuUtils::UserManagementChoice::REMOVE_USER:
            removeUser();
            break;
        case MenuUtils::UserManagementChoice::BACK:
            return;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
    }
    
   
}

void AdminMenu::showAccountManagementMenu() {
    MenuUtils::showHeader("ACCOUNT MANAGEMENT");
    std::cout << "Account Management Options:\n";
    std::cout << "1. Create New Account\n";
    std::cout << "2. Close Account\n";
    std::cout << "3. Back to Main Menu\n";
    std::cout << std::endl;
    
    int choice = MenuUtils::getChoice();
    
    switch (static_cast<MenuUtils::AccountManagementChoice>(choice)) {
        case MenuUtils::AccountManagementChoice::CREATE_ACCOUNT:
            createAccount();
            break;
        case MenuUtils::AccountManagementChoice::CLOSE_ACCOUNT:
            closeAccount();
            break;
        case MenuUtils::AccountManagementChoice::BACK:
            return;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
    }
}

void AdminMenu::handleLogout() {
    authController.logout();
    MenuUtils::showSuccess("Logged out successfully!\n");   
}

void AdminMenu::addNewAdmin() {
    MenuUtils::showHeader("ADD NEW ADMIN");
    std::string email = MenuUtils::getEmail();
    std::string password = MenuUtils::getPassword();
    
    Admin* admin = dynamic_cast<Admin*>(loginResult.user);
    if (admin && admin->requestAddAdmin(userManager, email, password)) {
        MenuUtils::showSuccess("Admin added successfully!\n");
    } else {
        MenuUtils::showError("Failed to add admin.\n");
    }
}

void AdminMenu::addNewAccountHolder() {
    MenuUtils::showHeader("ADD NEW ACCOUNT HOLDER");
    std::string email = MenuUtils::getEmail();
    std::string password = MenuUtils::getPassword();
    
    Admin* admin = dynamic_cast<Admin*>(loginResult.user);
    if (admin && admin->requestAddAccountHolder(userManager, email, password)) {
        MenuUtils::showSuccess("Account holder added successfully!\n");
    } else {
        MenuUtils::showError("Failed to add account holder.\n");
    }
}

void AdminMenu::removeUser() {
    MenuUtils::showHeader("REMOVE USER");
    std::string email = MenuUtils::getEmail();
    
    Admin* admin = dynamic_cast<Admin*>(loginResult.user);
    if (admin && admin->requestRemoveUser(userManager, email)) {
        MenuUtils::showSuccess("User removed successfully!");
    } else {
        MenuUtils::showError("Failed to remove user.");
    }
}

void AdminMenu::createAccount() {
    MenuUtils::showHeader("CREATE NEW ACCOUNT");
    std::cout << "User ID: ";
    uint32_t userId;
    std::cin >> userId;
    
    double initialDeposit = MenuUtils::getAmount();
    
    Admin* admin = dynamic_cast<Admin*>(loginResult.user);
    if (admin) {
        uint32_t accountNumber = admin->requestCreateAccount(loginResult, userId, initialDeposit);
        if (accountNumber != 0) {
            MenuUtils::showSuccess("Account created successfully! Account Number: " + std::to_string(accountNumber));
        } else {
            MenuUtils::showError("Failed to create account.");
        }
    }
}

void AdminMenu::closeAccount() {
    MenuUtils::showHeader("CLOSE ACCOUNT");
    std::cout << "Account Number: ";
    std::string accountNumber;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, accountNumber);
    
    Admin* admin = dynamic_cast<Admin*>(loginResult.user);
    if (admin && admin->requestCloseAccount(loginResult, accountNumber)) {
        MenuUtils::showSuccess("Account closed successfully!");
    } else {
        MenuUtils::showError("Failed to close account.");
    }
} 