#include "../../inc/Bank/Bank.hpp"
#include <stdexcept>

Bank* Bank::instance = nullptr;

Bank::Bank() : activeSessionToken(""), accounts(AccountArray(100)) {
}

Bank::~Bank() {
}

Bank* Bank::getInstance() {
    if (instance == nullptr) {
        instance = new Bank();
    }
    return instance;
}

std::string Bank::generateSessionToken() {
    int randomNum = rand() % 9000 + 1000;
    std::string token = "token_" + std::to_string(randomNum);
    return std::string(token);
}

std::string Bank::getSessionToken() {
    if(activeSessionToken == "") {
        activeSessionToken = generateSessionToken();
    }
    return activeSessionToken;
}

bool Bank::validateSessionToken(std::string token) {
    return !token.empty() && token == activeSessionToken;
}

Account* Bank::findAccount(uint32_t accountNumber) {
    Account* account = nullptr;
    for (int accountIndex = 0; accountIndex < accounts.getSize(); accountIndex++) {
        if (accounts[accountIndex] && accounts[accountIndex]->getAccountNumber() == accountNumber) {
            account = accounts[accountIndex];
            break;
        }
    }
    return account;
}

uint32_t Bank::generateAccountNumber() {
    static uint32_t accountNumber = 100;
    
    if (accountNumber == 100) {
        for (int accountIndex = 0; accountIndex < accounts.getSize(); accountIndex++) {
            if (accounts[accountIndex]->getAccountNumber() > accountNumber) {
                accountNumber = accounts[accountIndex]->getAccountNumber();
            }
        }
    }
    return accountNumber + 10;
}

bool Bank::processDeposit(uint32_t accountNumber, double amount, std::string token) {
    if (!validateSessionToken(token)) {
        throw std::runtime_error("Invalid session token");
    }
    if (amount <= 0) {
        throw std::runtime_error("Invalid amount");
    }
    
    Account* account = findAccount(accountNumber);
    if (!account) {
        throw std::runtime_error("Account not found");
    }
    
    return account->addTransaction(TransactionType::DEPOSIT, amount);
}

bool Bank::processWithdrawal(uint32_t accountNumber, double amount, std::string token) {
    if (!validateSessionToken(token)) {
        throw std::runtime_error("Invalid session token");
    }
    if (amount <= 0) {
        throw std::runtime_error("Invalid amount");
    }
    
    Account* account = findAccount(accountNumber);
    if (!account) {
        throw std::runtime_error("Account not found");
    }
    
    if (account->getBalance() < amount) {
        return false;
    }
    
    return account->addTransaction(TransactionType::WITHDRAW, amount);
}

uint32_t Bank::processCreateAccount(uint32_t accountHolderId, double initialDeposit, std::string token) {
    if (!validateSessionToken(token)) {
        throw std::runtime_error("Invalid session token");
    }
    if (initialDeposit < 0) {
        throw std::runtime_error("Invalid initial deposit");
    }
    
    uint32_t accountNumber = generateAccountNumber();
    
    accounts.add(new Account(accountNumber, accountHolderId, initialDeposit));
    
    return accountNumber;
}

bool Bank::processCloseAccount(uint32_t accountNumber, std::string token) {
    if (!validateSessionToken(token)) {
        throw std::runtime_error("Invalid session token");
    }
        
    return accounts.remove(accountNumber);
}

double Bank::processGetBalance(uint32_t accountNumber, std::string token) {
    if (!validateSessionToken(token)) {
        throw std::runtime_error("Invalid session token");
    }
    
    Account* account = findAccount(accountNumber);
    if (!account) {
        throw std::runtime_error("Account not found");
    }
    
    return account->getBalance();
}

TransactionArray Bank::processMiniStatement(uint32_t accountNumber, std::string token) {
    if (!validateSessionToken(token)) {
        throw std::runtime_error("Invalid session token");
    }
    
    Account* account = findAccount(accountNumber);
    if (!account) {
        throw std::runtime_error("Account not found");
    }
    
    return account->getMiniStatement(); 
}

TransactionArray Bank::processRangeStatement(uint32_t accountNumber, std::string token, std::string startDate, std::string endDate) {
    if (!validateSessionToken(token)) {
        throw std::runtime_error("Invalid session token");
    }
    
    Account* account = findAccount(accountNumber);
    if (!account) {
        throw std::runtime_error("Account not found");
    }
    
    return account->getRangeStatement(startDate, endDate);
}
