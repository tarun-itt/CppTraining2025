#include "../../inc/UI/MenuUtils.h"

namespace MenuUtils {
    void showHeader(const std::string& title) {
        std::cout << "==========================================" << std::endl;
        std::cout << "           " << title << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << std::endl;
    }
    
    int promptForChoice() {
        int choice;
        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice))
        {
            std::cout << "Please enter a valid Input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return choice;
    }
    
    std::string promptForEmail() {
        std::string email;
        std::cout << "Email: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, email);
        return email;
    }
    
    std::string promptForPassword(bool isSigningUp) {
        std::string password, confirmPassword;
        
        std::cout << "Password: ";
        std::getline(std::cin, password);
        
        if(isSigningUp){ 
            std::cout << "Confirm Password: ";
            std::getline(std::cin, confirmPassword);
                
            if (password != confirmPassword) {
                std::cout << "Passwords do not match. Please try again.\n";
                password = "";
            }
        }
        
        return password;
    }
    
    double promptForAmount(const std::string message) {
        double amount;
        do {
            std::cout << message;
            if (!(std::cin >> amount)) {
                std::cout << "Please enter a valid Amount\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else if (amount < 0) {
                std::cout << "Please enter a non-negative amount\n";
            } else {
                break;
            }
        } while (true);
        return amount;
    }
    
    uint32_t promptForUserId(){
        uint32_t userId;
        std::cout << "Enter User ID: ";
        if (!(std::cin >> userId))
        {
            std::cout << "Please enter a valid Input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return userId;
    }

    void showSuccess(const std::string& message) {
        std::cout << "Success: " << message << std::endl;
    }
    
    void showError(const std::string& message) {
        std::cout << "Fail: " << message << std::endl;
    }
} 