/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
enum tags{
    stop,
    start
};
//#define start 10
#define MACRO start



int main()
{
    #if start
    std::cout << "hii" << std::endl;
    #endif
    std::cout<<"Hello World";

    return 0;
}