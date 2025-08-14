#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#include "../inc/parser.h"
#include "../inc/jsonParser.h"
#include "../inc/csvParser.h"
#include "../inc/xmlParser.h"

enum class MenuOption {
    JSON = 1,
    CSV,
    XML,
    EXIT
};

void showMenu() {
    std::cout << "\n=== MENU ===" << std::endl;
    std::cout << "1. Parse JSON file" << std::endl;
    std::cout << "2. Parse CSV file" << std::endl; 
    std::cout << "3. Parse XML file" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int getValidChoice() {
    int choice;
    while (!(std::cin >> choice)) {
        std::cout << "Invalid input!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}

void parseFile(int choice) {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, filename);
    
    Parser* parser = nullptr;
    
    switch (choice) {
        case static_cast<int>(MenuOption::JSON):
            parser = new JsonParser(filename);
            break;
        case static_cast<int>(MenuOption::CSV):
            parser = new CsvParser(filename);
            break;
        case static_cast<int>(MenuOption::XML):
            parser = new XmlParser(filename);
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            return;
    }
    
    ParseResult result = parser->parse();
    if (!result.success()) {
        std::cout << "Error: " << result.message << std::endl;
        delete parser;
        return;
    }
    
    parser->print();
    delete parser;
}

int main() {
    int choice;
    do {
        showMenu();
        choice = getValidChoice();
        
        if (choice >= 1 && choice <= 3) {
            parseFile(choice);
        }
    } while (choice != 4);
    
    std::cout << "Bye!" << std::endl;
    return 0;
}