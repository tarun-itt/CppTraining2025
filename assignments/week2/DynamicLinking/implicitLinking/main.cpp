#include <iostream>
#include <limits>

#include "mathOperations.h"

enum MenuOptions{
    ADD = 1,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    EXIT
};


double handleInput(const char* message){
    double input = 0;
    
    while (true) {
        std::cout<<"Enter "<<message<<": ";
        std::cin >> input;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return input;
}

void runCalculator(){
    int choice;
    double num1 = 0.0, num2 = 0.0;
    double result;
    do{
        std::cout<<" ======= Calculator ======= \n\n";
        std::cout<<" Press 1 to Add\n";
        std::cout<<" Press 2 to Subtract\n";
        std::cout<<" Press 3 to Multiply\n";
        std::cout<<" Press 4 to Divide\n";
        std::cout<<" Press 5 to Exit\n";
        std::cout<<"\nChoice: ";
        choice = static_cast<int>(handleInput("Choice"));


        switch (choice)
        {
            case MenuOptions::ADD: {
                num1 = handleInput("first number");
                num2 = handleInput("second number");
                result = add(num1, num2);
            }
                break;
            case MenuOptions::SUBTRACT: {
                num1 = handleInput("first number");
                num2 = handleInput("second number");
                result = subtract(num1, num2);
            }
                break;
            case MenuOptions::MULTIPLY: {
                num1 = handleInput("multiplicant");
                num2 = handleInput("multiplier");
                result = multiply(num1, num2);
            }
                break;
            case MenuOptions::DIVIDE: {
                num1 = handleInput("dividend");
                while(true){
                    num2 = handleInput("divisor");
                    if (num2 == 0.0){
                        std::cout << "Divisor cannot be zero. Please try again.\n";
                    }else{
                        break;
                    }
                }   
                result = divide(num1, num2);
            }
                break;
            default:
                std::cout<<"Please enter a valid choice (1-5).\n\n";
                break;
        }

        if(choice < MenuOptions::EXIT && choice>=MenuOptions::ADD)
            std::cout<<"Result: "<<result<<"\n";
        
    }while(choice != MenuOptions::EXIT);
}

int main(){
    runCalculator();

    return 0;
}