#include <iostream>

#define PRINT_TO

int main()
{
#ifdef PRINT_TO //prints hello since this macro was defind
    std::cout << "hello\n";
#endif

#ifndef PRINT_NO //prints world since this macro was not defined
    std::cout << "world\n";
#endif

#if defined(PRINT_TO)
    std::cout<<"printed\n";
#elif  !defined(PRINT_TO)
    std::cout<<"not printed \n";
#endif

    return 0;
}