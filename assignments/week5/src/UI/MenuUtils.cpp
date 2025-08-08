#include "../../inc/UI/MenuUtils.hpp"

namespace MenuUtils {
    void showHeader(const std::string& title) {
        std::cout << "==========================================" << std::endl;
        std::cout << "           " << title << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << std::endl;
    }
    
    int getChoice() {
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
    
    std::string getEmail() {
        std::string email;
        std::cout << "Email: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, email);
        return email;
    }
    
    std::string getPassword() {
        std::string password;
        std::cout << "Password: ";
        std::getline(std::cin, password);
        return password;
    }
    
    double getAmount() {
        double amount;
        std::cout << "Amount: ";
        if (!(std::cin >> amount))
        {
            std::cout << "Please enter a valid Amount\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return amount;
    }
    
    void showSuccess(const std::string& message) {
        std::cout << "Success: " << message << std::endl;
    }
    
    void showError(const std::string& message) {
        std::cout << "Fail: " << message << std::endl;
    }
} 