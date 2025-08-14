#ifndef LOGINRESULT_HPP
#define LOGINRESULT_HPP

#include <string>

#include "../Bank/Bank.hpp"
#include "../entities/User.hpp"

struct LoginResult {
    Bank* bank;
    User* user;
    std::string sessionToken;
};

#endif