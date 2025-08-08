#include "../../inc/roles/AccountHolder.hpp"
#include "../../inc/auth/LoginResult.hpp"

#include <cstdint>

AccountHolder::AccountHolder(const std::string& email, const std::string& password): User(email, password) {
}

uint32_t AccountHolder::getAccountNumber() const {
    return accountNumber;
}

bool AccountHolder::requestDeposit(const LoginResult& loginResult, double amount) {
    return loginResult.bank->processDeposit(accountNumber, amount, loginResult.sessionToken);
}

bool AccountHolder::requestWithdraw(const LoginResult& loginResult, double amount) {
    return loginResult.bank->processWithdrawal(accountNumber, amount, loginResult.sessionToken);
}

void AccountHolder::setAccountNumber(uint32_t accountNumber) {
    this->accountNumber = accountNumber;
}