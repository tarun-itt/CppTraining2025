#include <ctime>
#include <cstdlib>

#include "../inc/entities/UserDatabaseManager.h"
#include "../inc/auth/AuthController.h"
#include "../inc/UI/LoginMenu.h"
#include "../inc/UI/AdminMenu.h"
#include "../inc/UI/AccountMenu.h"

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