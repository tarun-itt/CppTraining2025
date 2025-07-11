#include <iostream>

int main()
{
    std::string myString;
    int age, num;

    std::cout << "Input:";
    // std::cin>>myString;
    // std::cout<<myString; //doesnt take space seaprated iputs
    std::cin >> age;
    std::cin >> num;
    std::cout << age << " " << num;
    std::cin.get();
    std::cout << "\nInput: ";
    std::getline(std::cin, myString);
    std::cout << "\n"
              << myString << "\n";

    return 0;
}