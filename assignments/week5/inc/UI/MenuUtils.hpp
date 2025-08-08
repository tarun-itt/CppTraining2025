#ifndef MENUUTILS_HPP
#define MENUUTILS_HPP

#include <iostream>
#include <string>
#include <limits>

namespace MenuUtils {
    enum class MainMenuChoice {
        LOGIN = 1,
        EXIT = 2
    };
    
    enum class AdminMenuChoice {
        USER_MANAGEMENT = 1,
        ACCOUNT_MANAGEMENT = 2,
        LOGOUT = 3
    };
    
    enum class AccountMenuChoice {
        TRANSACTIONS = 1,
        ACCOUNT_INFO = 2,
        LOGOUT = 3
    };
    
    enum class UserManagementChoice {
        ADD_ADMIN = 1,
        ADD_ACCOUNT_HOLDER = 2,
        REMOVE_USER = 3,
        BACK = 4
    };
    
    enum class AccountManagementChoice {
        CREATE_ACCOUNT = 1,
        CLOSE_ACCOUNT = 2,
        BACK = 3
    };
    
    enum class TransactionChoice {
        DEPOSIT = 1,
        WITHDRAW = 2,
        BACK = 3
    };
    
    void showHeader(const std::string& title);
    int getChoice();
    std::string getEmail();
    std::string getPassword();
    double getAmount();
    void showSuccess(const std::string& message);
    void showError(const std::string& message);
    bool validateEmail(const std::string& email);
}

#endif 