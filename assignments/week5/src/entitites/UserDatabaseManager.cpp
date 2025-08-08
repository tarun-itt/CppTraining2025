#include "../../inc/entitites/UserDatabaseManager.hpp"
#include "../../inc/roles/Admin.hpp"
#include "../../inc/roles/AccountHolder.hpp"

UserDatabaseManager::UserDatabaseManager() {
    addAdmin("admin@bank.com", "admin123"); //default admin
}

bool UserDatabaseManager::addAdmin(const std::string& email, const std::string& password) {
    if(findUser(email) != nullptr) {
        return false;
    }
    Admin* admin = new Admin(email, password);
    admins.add(admin);
    return true;
}

bool UserDatabaseManager::addAccountHolder(const std::string& email, const std::string& password) {
    if(findUser(email) != nullptr) {
        return false;
    }
    AccountHolder* accountHolder = new AccountHolder(email, password);
    accountHolders.add(accountHolder);         
    return true;
}

bool UserDatabaseManager::removeUser(const std::string& email) {
    const User* user = findUser(email);
    if (user == nullptr) {
        return false;
    }

    if (dynamic_cast<const Admin*>(user) != nullptr) {
        admins.remove(email);
    } else if (dynamic_cast<const AccountHolder*>(user) != nullptr) {
        accountHolders.remove(email);
    }

    return true;
}

User* UserDatabaseManager::findUser(const std::string& email) {
    User* user = nullptr;

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
