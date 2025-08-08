#include "../../inc/roles/Admin.hpp"
#include "../../inc/auth/LoginResult.hpp"
#include "../../inc/roles/AccountHolder.hpp"
#include <cstdint>

Admin::Admin(const std::string& email, const std::string& password)
    : User(email, password) {
}

bool Admin::requestAddAdmin(UserDatabaseManager& userManager, const std::string& email, const std::string& password) {
    return userManager.addAdmin(email, password);
}

bool Admin::requestAddAccountHolder(UserDatabaseManager& userManager, const std::string& email, const std::string& password) {
    return userManager.addAccountHolder(email, password);
}

bool Admin::requestRemoveUser(UserDatabaseManager& userManager, const std::string& email) {
    return userManager.removeUser(email);
}

uint32_t Admin::requestCreateAccount(const LoginResult& loginResult, uint32_t userId, double initialDeposit) {
    return loginResult.bank->processCreateAccount(userId, initialDeposit, loginResult.sessionToken);
}

bool Admin::requestCloseAccount(const LoginResult& loginResult, const std::string& accountNumber) {
    uint32_t accNum = std::stoul(accountNumber);
    return loginResult.bank->processCloseAccount(accNum, loginResult.sessionToken);
}
