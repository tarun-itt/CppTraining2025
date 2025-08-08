#include <ctime>
#include <cstdlib>
#include "../inc/entitites/UserDatabaseManager.hpp"
#include "../inc/auth/AuthController.hpp"
#include "../inc/UI/LoginMenu.hpp"
#include "../inc/UI/AdminMenu.hpp"
#include "../inc/UI/AccountMenu.hpp"

int main() {
    srand(time(nullptr));

    UserDatabaseManager userManager;
    AuthController authController(userManager);
    
    bool running = true;
    
    while (running) {
        LoginMenu loginMenu(authController);
        LoginResult result = loginMenu.run();
        
        if (result.user == nullptr || result.bank == nullptr) {
            running = false;
            continue;
        }

        if (authController.isAdminLoggedIn()) {
            AdminMenu adminMenu(authController, result, userManager);
            adminMenu.run();
        } else {
            AccountMenu accountMenu(authController, result);
            accountMenu.run();
        }
    }
    
    return 0;
}