#include "../../inc/UI/AccountMenu.hpp"
#include "../../inc/roles/AccountHolder.hpp"
#include <iostream>
#include <limits>

AccountMenu::AccountMenu(AuthController& authController, LoginResult& loginResult)
    : authController(authController), loginResult(loginResult) {
}

AccountMenu::~AccountMenu() {
}

void AccountMenu::run() {
    bool running = true;
    
    while (running) {
        showMainMenu();
        int choice = MenuUtils::getChoice();
        
        switch (static_cast<MenuUtils::AccountMenuChoice>(choice)) {
            case MenuUtils::AccountMenuChoice::TRANSACTIONS:
                showTransactionMenu();
                break;
            case MenuUtils::AccountMenuChoice::ACCOUNT_INFO:
                showAccountInfo();
                break;
            case MenuUtils::AccountMenuChoice::LOGOUT:
                handleLogout();
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

void AccountMenu::showMainMenu() {
    MenuUtils::showHeader("ACCOUNT HOLDER DASHBOARD");
    std::cout << "Welcome, Account Holder!" << std::endl;
    std::cout << std::endl;
    std::cout << "Please select an option:" << std::endl;
    std::cout << "1. Transactions" << std::endl;
    std::cout << "2. Account Information" << std::endl;
    std::cout << "3. Logout" << std::endl;
    std::cout << std::endl;
}

void AccountMenu::showTransactionMenu() {
    MenuUtils::showHeader("TRANSACTIONS");
    std::cout << "Transaction Options:" << std::endl;
    std::cout << "1. Deposit" << std::endl;
    std::cout << "2. Withdraw" << std::endl;
    std::cout << "3. Back to Main Menu" << std::endl;
    std::cout << std::endl;
    
    int choice = MenuUtils::getChoice();
    
    switch (static_cast<MenuUtils::TransactionChoice>(choice)) {
        case MenuUtils::TransactionChoice::DEPOSIT:
            performDeposit();
            break;
        case MenuUtils::TransactionChoice::WITHDRAW:
            performWithdraw();
            break;
        case MenuUtils::TransactionChoice::BACK:
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
    }
}

void AccountMenu::showAccountInfo() {
    MenuUtils::showHeader("ACCOUNT INFORMATION");
    //std::cout << "Account Number: " << loginResult.user->getAccountNumber() << std::endl;
}

void AccountMenu::handleLogout() {
    authController.logout();
    MenuUtils::showSuccess("Logged out successfully!");
}

void AccountMenu::performDeposit() {
    MenuUtils::showHeader("DEPOSIT");
    double amount = MenuUtils::getAmount();
    
    if (amount > 0) {
        AccountHolder* accountHolder = (AccountHolder*)(loginResult.user);
        if (accountHolder && accountHolder->requestDeposit(loginResult, amount)) {
            MenuUtils::showSuccess("Deposit successful! Amount: " + std::to_string(amount));
        } else {
            MenuUtils::showError("Deposit failed.");
        }
    } else {
        MenuUtils::showError("Invalid amount. Please enter a positive value.");
    }
}

void AccountMenu::performWithdraw() {
    MenuUtils::showHeader("WITHDRAW");
    double amount = MenuUtils::getAmount();
    
    if (amount > 0) {
        AccountHolder* accountHolder = dynamic_cast<AccountHolder*>(loginResult.user);
        if (accountHolder && accountHolder->requestWithdraw(loginResult, amount)) {
            MenuUtils::showSuccess("Withdrawal successful! Amount: " + std::to_string(amount));
        } else {
            MenuUtils::showError("Withdrawal failed. Insufficient funds or invalid amount.");
        }
    } else {
        MenuUtils::showError("Invalid amount. Please enter a positive value.");
    }
} 