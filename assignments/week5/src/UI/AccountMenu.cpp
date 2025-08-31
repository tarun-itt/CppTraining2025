#include <iostream>
#include <limits>

#include "../../inc/UI/AccountMenu.h"
#include "../../inc/roles/AccountHolder.h"

AccountMenu::AccountMenu(AuthController& authController, LoginResult& loginResult)
    : authController(authController), loginResult(loginResult) {
}

AccountMenu::~AccountMenu() {
}

void AccountMenu::run() {
    bool running = true;
    
    while (running) {
        showMainMenu();
        int choice = MenuUtils::promptForChoice();
        
        switch (static_cast<MenuUtils::AccountMenuChoice>(choice)) {
            case MenuUtils::AccountMenuChoice::TRANSACTIONS: {
                showTransactionMenu();
                break;
            }
            case MenuUtils::AccountMenuChoice::ACCOUNT_INFO: {
                showAccountInfo();
                break;
            }
            case MenuUtils::AccountMenuChoice::LOGOUT: {
                handleLogout();
                running = false;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
    }
}

void AccountMenu::showMainMenu() {
    MenuUtils::showHeader("ACCOUNT MENU");
    std::cout << std::endl;
    std::cout << "Please select an option:" << std::endl;
    std::cout << "1. Transactions" << std::endl;
    std::cout << "2. Account Information" << std::endl;
    std::cout << "3. Logout" << std::endl;
    std::cout << std::endl;
}

void AccountMenu::showTransactionMenu() {
    AccountHolder* accountHolder = dynamic_cast<AccountHolder*>(loginResult.user);
    
    if(accountHolder->getAccountNumber()) {
        MenuUtils::showHeader("TRANSACTIONS");
        std::cout << "Transaction Options:" << std::endl;
        std::cout << "1. Deposit" << std::endl;
        std::cout << "2. Withdraw" << std::endl;
        std::cout << "3. Mini Statement" << std::endl;
        std::cout << "4. Full Statement" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;
        std::cout << std::endl;
        
        int choice = MenuUtils::promptForChoice();
        
        switch (static_cast<MenuUtils::TransactionChoice>(choice)) {
            case MenuUtils::TransactionChoice::DEPOSIT: {
                showTransactionMenu(TransactionType::DEPOSIT);
                break;
            }
            case MenuUtils::TransactionChoice::WITHDRAW: {
                showTransactionMenu(TransactionType::WITHDRAW);
                break;
            }
            case MenuUtils::TransactionChoice::MINI_STATEMENT: {
                printMiniStatement();
                break;
            }
            case MenuUtils::TransactionChoice::RANGE_STATEMENT: {
                printFullStatement();
                break;
            }
            case MenuUtils::TransactionChoice::BACK:{
                return;
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
    }else {
        MenuUtils::showError("You don't have an account yet!");
    }
}

void AccountMenu::showAccountInfo() {
    MenuUtils::showHeader("ACCOUNT INFORMATION");
    AccountHolder* accountHolder = dynamic_cast<AccountHolder*>(loginResult.user);
    if(accountHolder->getAccountNumber()) {
        std::cout<< "User ID: " << accountHolder->getUserId() << std::endl;
        std::cout << "Account Number: " << accountHolder->getAccountNumber() << std::endl;
        std::cout<< "Email: " << accountHolder->getEmail() << std::endl;
        std::cout<< "Balance: " << loginResult.bank->processGetBalance(accountHolder->getAccountNumber(), loginResult.sessionToken) << std::endl;
    }else {
        MenuUtils::showError("You don't have an account yet!");
    }
}

void AccountMenu::handleLogout() {
    authController.logout();
    MenuUtils::showSuccess("Logged out successfully!");
}

void AccountMenu::printMiniStatement() {
    AccountHolder *accountHolder = dynamic_cast<AccountHolder*>(loginResult.user);
    TransactionLedger miniTransactions = loginResult.bank->processMiniStatement(accountHolder->getAccountNumber(), loginResult.sessionToken);

    for(int transactionIndex = 0; transactionIndex < miniTransactions.getSize(); transactionIndex++){
        Transaction* currentTransaction = miniTransactions[transactionIndex];
        if (currentTransaction != nullptr) {
            std::cout << "Transaction " << transactionIndex + 1 << ":" << std::endl;
            std::cout << "Type: " << (currentTransaction->getType() == TransactionType::DEPOSIT ? "Deposit" : "Withdrawal") << std::endl;
            std::cout << "Amount: " << currentTransaction->getAmount() << std::endl;
            std::cout << "Balance After Transaction: " << currentTransaction->getBalanceAfterTransaction() << std::endl;
            std::cout << "Date: " << currentTransaction->getTimestamp() << std::endl;
            std::cout << "--------------------------------" << std::endl;
        }
    }
}

void AccountMenu::printFullStatement() {
    AccountHolder *accountHolder = dynamic_cast<AccountHolder*>(loginResult.user);  
    TransactionLedger fullTransactions = loginResult.bank->processStatementInDateRange(accountHolder->getAccountNumber(), loginResult.sessionToken, "2025-01-01", "2025-10-31");

    for(int transactionIndex = 0; transactionIndex < fullTransactions.getSize(); transactionIndex++){
        Transaction* currentTransaction = fullTransactions[transactionIndex];
        if (currentTransaction != nullptr) {
            std::cout << "Transaction " << transactionIndex + 1 << ":" << std::endl;
            std::cout << "Type: " << (currentTransaction->getType() == TransactionType::DEPOSIT ? "Deposit" : "Withdrawal") << std::endl;
            std::cout << "Amount: " << currentTransaction->getAmount() << std::endl;
            std::cout << "Balance After Transaction: " << currentTransaction->getBalanceAfterTransaction() << std::endl;
            std::cout << "Date: " << currentTransaction->getTimestamp() << std::endl;
            std::cout << "--------------------------------" << std::endl;
        }
    }
}

void AccountMenu::showTransactionMenu(TransactionType type) {
    std::string transactionTypeName = type == TransactionType::WITHDRAW ? "WITHDRAW" : "DEPOSIT";
    MenuUtils::showHeader(transactionTypeName);
    
    double amount = MenuUtils::promptForAmount();
    try{
        if (amount > 0) {
            AccountHolder* accountHolder = dynamic_cast<AccountHolder*>(loginResult.user);
            if (accountHolder) {
                bool transactionSuccess = false;

                if(type == TransactionType::DEPOSIT){
                    transactionSuccess = accountHolder->requestDeposit(loginResult, amount);
                }else{
                    transactionSuccess = accountHolder->requestWithdraw(loginResult, amount);
                }

                if (transactionSuccess) {
                    std::string successMsg = (type == TransactionType::DEPOSIT) ? "Deposit successful! Amount: " + std::to_string(amount) : "Withdrawal successful! Amount: " + std::to_string(amount); 
                    MenuUtils::showSuccess(successMsg);
                } else {
                    std::string errorMsg = (type == TransactionType::DEPOSIT) ? "Deposit failed." : "Withdrawal failed. Insufficient funds.";
                    MenuUtils::showError(errorMsg);
                }
            } else {
                MenuUtils::showError("Account Holder doesn not exist!");
            }
        } else {
            MenuUtils::showError("Invalid amount. Please enter a positive value.");
        }
    } catch (const std::runtime_error& e) {
        MenuUtils::showError(e.what());
    }
}