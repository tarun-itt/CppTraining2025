#include "../../inc/auth/AuthController.hpp"
#include "../../inc/roles/Admin.hpp"
#include "../../inc/roles/AccountHolder.hpp"
#include <string>

AuthController::AuthController(UserDatabaseManager& userManager): currentUser(nullptr), userManager(userManager) {
}

LoginResult AuthController::login(const std::string& email, const std::string& password) {
    LoginResult result;
    result.user = nullptr;
    result.bank = nullptr;
    result.sessionToken = "";

    User* foundUser = userManager.findUser(email);
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

User* AuthController::getCurrentUser() {
    return currentUser;
}

bool AuthController::isAdminLoggedIn() {
    return currentUser != nullptr && dynamic_cast<Admin*>(currentUser) != nullptr;
}