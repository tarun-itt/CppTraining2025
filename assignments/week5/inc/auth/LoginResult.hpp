#ifndef LOGINRESULT_HPP
#define LOGINRESULT_HPP

#include <string>
#include "../Bank/Bank.hpp"
#include "../entitites/User.hpp"

struct LoginResult {
    Bank* bank;
    User* user;
    std::string sessionToken;
};

#endif