#ifndef MENUUTILS_HPP
#define MENUUTILS_HPP

#include <iostream>
#include <string>
#include <limits>

namespace MenuUtils {
    enum class MainMenuChoice {
        LOGIN = 1,
        EXIT
    };
    
    enum class AdminMenuChoice {
        USER_MANAGEMENT = 1,
        ACCOUNT_MANAGEMENT,
        LOGOUT
    };
    
    enum class AccountMenuChoice {
        TRANSACTIONS = 1,
        ACCOUNT_INFO,
        LOGOUT
    };
    
    enum class UserManagementChoice {
        ADD_ADMIN = 1,
        ADD_ACCOUNT_HOLDER,
        REMOVE_USER,
        BACK
    };
    
    enum class AccountManagementChoice {
        CREATE_ACCOUNT = 1,
        CLOSE_ACCOUNT,
        BACK
    };
    
    enum class TransactionChoice {
        DEPOSIT = 1,
        WITHDRAW,
        MINI_STATEMENT,
        RANGE_STATEMENT,
        BACK
    };

    enum class UserType {
        ADMIN = 1,
        ACCOUNT_HOLDER
    };
    
    void showHeader(const std::string& title);
    int promptForChoice();
    std::string promptForEmail();
    std::string promptForPassword(bool isSigningUp = false);
    double promptForAmount();
    uint32_t promptForUserId();
    void showSuccess(const std::string& message);
    void showError(const std::string& message);
    bool validateEmail(const std::string& email);
}

#endif 