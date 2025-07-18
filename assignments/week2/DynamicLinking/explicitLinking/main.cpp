#include <iostream>
#include <limits>
#include <string>
#include <dlfcn.h>

struct Operators
{
    double (*addPtr)(double, double);
    double (*subtractPtr)(double, double);
    double (*multiplyPtr)(double, double);
    double (*dividePtr)(double, double);
};


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
            break;
        }
    }
    return input;
}

void init(Operators& mathFunction){
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
                result = mathFunction.addPtr(num1, num2);
                std::cout<<"Result: "<<result<<"\n";
            }
                break;
            case 2: {
                num1 = handleInput("first number");
                num2 = handleInput("second number");
                result = mathFunction.subtractPtr(num1, num2);
                std::cout<<"Result: "<<result<<"\n";
            }
                break;
            case 3: {
                num1 = handleInput("multiplicant");
                num2 = handleInput("multiplier");
                result = mathFunction.multiplyPtr(num1, num2);
                std::cout<<"Result: "<<result<<"\n";
            }
                break;
            case 4: {
                num1 = handleInput("dividend");
                num2 = handleInput("divisor");
                result = mathFunction.dividePtr(num1, num2);
                std::cout<<"Result: "<<result<<"\n";
            }
                break;
            default:
                break;
        }
        
    }while(choice != 5);
}

int main(){
    void* handle = dlopen("../lib/libmathOperations.so", RTLD_LAZY);
    if (!handle)
    {
        std::cout << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }

    Operators mathFunction;
    mathFunction.addPtr = (double (*)(double, double))dlsym(handle,"add");
    mathFunction.subtractPtr = (double (*)(double, double))dlsym(handle,"subtract");
    mathFunction.multiplyPtr = (double (*)(double, double))dlsym(handle,"multiply");
    mathFunction.dividePtr = (double (*)(double, double))dlsym(handle,"divide");
    init(mathFunction);

    dlclose(handle);

    return 0;
}