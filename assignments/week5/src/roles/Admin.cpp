#include <cstdint>
#include <stdexcept>

#include "../../inc/roles/Admin.hpp"
#include "../../inc/auth/LoginResult.hpp"
#include "../../inc/roles/AccountHolder.hpp"

Admin::Admin(const std::string& email, const std::string& password, uint32_t userId)
    : User(email, password, userId) {
}

uint32_t Admin::requestAddAdmin(UserDatabaseManager& userManager, const std::string& email, const std::string& password) {
    return userManager.addAdmin(email, password);
}

uint32_t Admin::requestAddAccountHolder(UserDatabaseManager& userManager, const std::string& email, const std::string& password) {
    return userManager.addAccountHolder(email, password);
}

bool Admin::requestRemoveUser(UserDatabaseManager& userManager, const std::string& email) {
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
