#ifndef IUSERDATABASEMANAGER_HPP
#define IUSERDATABASEMANAGER_HPP

#include <cstdint>
#include <string>

class IUser;

class IUserDatabaseManager {
public:
    virtual ~IUserDatabaseManager() = default;
    
    virtual IUser* findUser(const std::string& email) = 0;
    virtual IUser* findUser(uint32_t userId) = 0;
    virtual void setAccountNumber(uint32_t userId, uint32_t accountNumber) = 0;
    
    virtual uint32_t generateUserId() = 0;
    virtual uint32_t addAdmin(const std::string& email, const std::string& password) = 0;
    virtual uint32_t addAccountHolder(const std::string& email, const std::string& password) = 0;
    virtual bool removeUser(const std::string& email) = 0;
};

#endif 