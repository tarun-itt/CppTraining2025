#include <string>
#include <stdexcept>

#include "../../inc/auth/AuthController.h"
#include "../../inc/roles/Admin.h"
#include "../../inc/roles/AccountHolder.h"
#include "../../inc/Bank/Bank.h"

AuthController::AuthController(UserDatabaseManager& userManager): currentUser(nullptr), userManager(userManager) {
}

LoginResult AuthController::login(const std::string& email, const std::string& password) {
    LoginResult result;
    result.user = nullptr;
    result.bank = nullptr;
    result.sessionToken = "";

if (!isEmailValid(email)) {
        throw std::invalid_argument("Invalid email");
    }

    IUser* foundUser = userManager.findUser(email);
    if (foundUser && foundUser->getPassword() == password) {
        result.bank = Bank::getInstance();
        result.sessionToken = result.bank->getSessionToken();
        currentUser = foundUser;
        result.user = currentUser;
        return result;
    }
    
    return result;
}

bool AuthController::logout() {
    currentUser = nullptr;
    return true;
}

IUser* AuthController::getCurrentUser() {
    return currentUser;
}

bool AuthController::isAdminLoggedIn() {
    return currentUser != nullptr && dynamic_cast<Admin*>(currentUser) != nullptr;
}

bool AuthController::isEmailValid(const std::string& email){
    int atPosition = -1, dotPosition = -1;
    bool isValid = true;

    for (int charIndex = 0; charIndex < (int)email.length(); charIndex++) {
        if (email[charIndex] == '@') {
            atPosition = charIndex;
        } else if (email[charIndex] == '.') {
            dotPosition = charIndex;
        }
    }

    if (atPosition == -1 || dotPosition == -1)
        isValid = false;

    if (atPosition > dotPosition)
        isValid = false;

    if (dotPosition >= (email.length() - 1))
        isValid = false;

    return isValid;
}