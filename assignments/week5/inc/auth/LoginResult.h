#ifndef LOGINRESULT_HPP
#define LOGINRESULT_HPP

#include <string>

#include "../interfaces/IBank.h"
#include "../interfaces/IUser.h"

struct LoginResult {
    IBank* bank;
    IUser* user;
    std::string sessionToken;
};

#endif