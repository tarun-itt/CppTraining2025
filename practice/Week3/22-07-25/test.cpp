#include <iostream>

int main()
{
    int x{ 1 };
    int& ref{ x };

    std::cout << x << ref << '\n';

    int y{ 2 };
    ref = y;
    y = 3;

    std::cout << x << ref << '\n';

    x = 4;

    std::cout << x << ref << '\n';

    int* ptr;

    if(ptr){
        std::cout<<"PRINTED\n"; //gets printed even though ptr is wild, or even dangling, because we can only check for ptr to be null or not
    }
    //*ptr=12; //segmentation fault (because no memory address assigned)
   // std::cout<<*ptr<<"  "<<(*ptr + 10)<<std::endl; //wild pointer, undefined behaviour

    std::cout<<*(&x)<<std::endl; //&gets address of given object, * retrieves the object at a given address
    return 0;
}