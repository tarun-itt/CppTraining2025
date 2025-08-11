#include <string>

#include "../../inc/entities/User.hpp"
#include "../../inc/auth/LoginResult.hpp"

User::User(const std::string& email, const std::string& password, const uint32_t userId) 
    : email(email), password(password), userId(userId) {
}

std::string User::getEmail() const {
    return email;
}

std::string User::getPassword() const {
    return password;
}

uint32_t User::getUserId() const {
    return userId;
}

double User::requestBalance(const LoginResult& loginResult, uint32_t accountNumber) {
    return loginResult.bank->processGetBalance(accountNumber, loginResult.sessionToken);
}

TransactionLedger User::requestMiniStatement(const LoginResult& loginResult, uint32_t accountNumber) {
    return (loginResult.bank->processMiniStatement(accountNumber, loginResult.sessionToken));
}

TransactionLedger User::requestRangeStatement(const LoginResult& loginResult, uint32_t accountNumber, std::string startDate, std::string endDate) {
    return (loginResult.bank->processRangeStatement(accountNumber, loginResult.sessionToken, startDate, endDate));
}
