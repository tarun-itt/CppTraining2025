#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

std::ostream& operator<<(std::ostream& out, const Employee& e)
{
    out << e.id << ' ' << e.age << ' ' << e.wage;
    return out;
}

int main()
{
    Employee joe { 2, 28 };
    //std::cout << joe << '\n';
    int* p = &joe.id;

    std::cout<<(p)<<std::endl;

    return 0;
}