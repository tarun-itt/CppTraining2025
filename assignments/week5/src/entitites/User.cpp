#include "../../inc/entitites/User.hpp"
#include "../../inc/auth/LoginResult.hpp"
#include <string>

User::User(const std::string& email, const std::string& password) 
    : email(email), password(password) {
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

TransactionArray User::requestMiniStatement(const LoginResult& loginResult, uint32_t accountNumber) {
    return (loginResult.bank->processMiniStatement(accountNumber, loginResult.sessionToken));
}

TransactionArray User::requestRangeStatement(const LoginResult& loginResult, uint32_t accountNumber, std::string startDate, std::string endDate) {
    return (loginResult.bank->processRangeStatement(accountNumber, loginResult.sessionToken, startDate, endDate));
}
