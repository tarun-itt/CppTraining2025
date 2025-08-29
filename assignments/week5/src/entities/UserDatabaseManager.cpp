#include <cstdint>

#include "../../inc/entities/UserDatabaseManager.h"
#include "../../inc/roles/Admin.h"
#include "../../inc/roles/AccountHolder.h"

UserDatabaseManager::UserDatabaseManager() {
    addAdmin("admin@bank.com", "admin123"); //default admin
}

uint32_t UserDatabaseManager::generateUserId(){
    static uint32_t lastUserId = 100;
    lastUserId += rand() % 100 + 1;
    return lastUserId;
}

uint32_t UserDatabaseManager::addAdmin(const std::string& email, const std::string& password) {
    uint32_t userId = generateUserId();

    if(findUser(email) == nullptr) {
        Admin* admin = new Admin(email, password, userId);
        admins.add(admin);
    }
    
    return userId;
}

uint32_t UserDatabaseManager::addAccountHolder(const std::string& email, const std::string& password) {
    uint32_t userId = generateUserId();

    if(findUser(email) == nullptr) {
        AccountHolder* accountHolder = new AccountHolder(email, password, userId);
        accountHolders.add(accountHolder);    
    }
    return userId;
}
    
bool UserDatabaseManager::removeUser(const std::string& email) {
    bool success = false;
    const IUser* user = findUser(email);

    if (user == nullptr) {
        if (dynamic_cast<const Admin*>(user) != nullptr) {
            admins.remove(email);
        } else if (dynamic_cast<const AccountHolder*>(user) != nullptr) {
            accountHolders.remove(email);
        }
        success = true;
    }

    return success;
}

IUser* UserDatabaseManager::findUser(const std::string& email) {
    IUser* user = nullptr;

    for (int userIndex = 0; userIndex < admins.getSize(); userIndex++) {
        if (admins[userIndex]->getEmail() == email) {
            user = admins[userIndex];
            break;
        }
    }
        
    for (int userIndex = 0; userIndex < accountHolders.getSize(); userIndex++) {
        if (accountHolders[userIndex]->getEmail() == email) {
            user = accountHolders[userIndex];
            break;
        }
    }
    
    return user;
}

IUser* UserDatabaseManager::findUser(uint32_t userId) {
    IUser* user = nullptr;

    for (int userIndex = 0; userIndex < admins.getSize(); userIndex++) {
        if (admins[userIndex]->getUserId() == userId) {
            user = admins[userIndex];
            break;
        }
    }
        
    for (int userIndex = 0; userIndex < accountHolders.getSize(); userIndex++) {
        if (accountHolders[userIndex]->getUserId() == userId) {
            user = accountHolders[userIndex];
            break;
        }
    }
    
    return user;
}

void UserDatabaseManager::setAccountNumber(uint32_t userId, uint32_t accountNumber) {
    AccountHolder* accountHolder = dynamic_cast<AccountHolder*>(findUser(userId));
    if (accountHolder != nullptr) {
        accountHolder->setAccountNumber(accountNumber);
    }
}