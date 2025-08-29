#include <cstdint>
#include <stdexcept>

#include "../../inc/roles/Admin.h"
#include "../../inc/auth/LoginResult.h"
#include "../../inc/roles/AccountHolder.h"

Admin::Admin(const std::string& email, const std::string& password, uint32_t userId)
    : User(email, password, userId) {
}

uint32_t Admin::requestAddAdmin(UserDatabaseManager& userManager, const std::string& email, const std::string& password) {
    return userManager.addAdmin(email, password);
}

uint32_t Admin::requestAddAccountHolder(LoginResult& loginResult, UserDatabaseManager& userManager, const std::string& email, const std::string& password, double initialDeposit) {
    uint32_t userId = userManager.addAccountHolder(email, password);
    this->requestCreateAccount(loginResult, userManager, userId, initialDeposit);
    return userId;
}

bool Admin::requestRemoveUser(LoginResult& loginResult, UserDatabaseManager& userManager, const std::string& email) {
    IUser* user = userManager.findUser(email);
    if(user == nullptr) {
        throw std::runtime_error("User not found");
    }
    AccountHolder* accountUser = dynamic_cast<AccountHolder*>(user);
    if(accountUser != nullptr) {
        this->requestCloseAccount(loginResult, accountUser->getAccountNumber());
    }
    return userManager.removeUser(email);
}

uint32_t Admin::requestCreateAccount(const LoginResult& loginResult, UserDatabaseManager& userManager, uint32_t userId, double initialDeposit) {
    if(userManager.findUser(userId) != nullptr) {
        uint32_t accountNumber = loginResult.bank->processCreateAccount(userId, initialDeposit, loginResult.sessionToken);
        userManager.setAccountNumber(userId, accountNumber);
        return accountNumber;
    }else {
        throw std::runtime_error("User not found");
    }

}

bool Admin::requestCloseAccount(const LoginResult& loginResult, uint32_t accountNumber) {
    return loginResult.bank->processCloseAccount(accountNumber, loginResult.sessionToken);
}
