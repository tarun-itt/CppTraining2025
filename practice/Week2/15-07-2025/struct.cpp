#include <iostream>

struct CD
{

    char a;
    double e;
    int b;
};

int main()
{
    struct CD a
    {
        '1', 1
    };
    std::cout << &a << "\n";
    std::cout << (void *)&a.a << " " << &a.e << " " << &a.b << "\n";
    std::cout << alignof(a) << std::endl
              << sizeof(a) << std::endl;
    return 0;
}
