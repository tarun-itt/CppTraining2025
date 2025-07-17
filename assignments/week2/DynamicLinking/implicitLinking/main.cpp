#include "../include/mathOperations.h"
#include <iostream>
#include <limits>
#include <string>


double handleInput(std::string message){
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
            return input;
        }
    }
    return input;
}

void init(){
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
        std::cout<<"\n Choice: ";
        choice = static_cast<int>(handleInput("Choice"));


        switch (choice)
        {
            case 1: {
                num1 = handleInput("first number");
                num2 = handleInput("second number");
                result = add(num1, num2);
                std::cout<<"Result: "<<result<<"\n";
            }
                break;
            case 2: {
                num1 = handleInput("first number");
                num2 = handleInput("second number");
                result = subtract(num1, num2);
                std::cout<<"Result: "<<result<<"\n";
            }
                break;
            case 3: {
                num1 = handleInput("multiplicant");
                num2 = handleInput("multiplier");
                result = multiply(num1, num2);
                std::cout<<"Result: "<<result<<"\n";
            }
                break;
            case 4: {
                num1 = handleInput("dividend");
                num2 = handleInput("divisor");
                result = divide(num1, num2);
                std::cout<<"Result: "<<result<<"\n";
            }
                break;
            default:
                break;
        }
        
    }while(choice != 5);
}

int main(){
    init();

    return 0;
}

