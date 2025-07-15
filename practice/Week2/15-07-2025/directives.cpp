#include <iostream>


int main(){
#ifdef TO_REPLACE
    std::cout<< "defined\n";

#else
    std::cout<<"not\n";
#endif

#define TO_REPLACE "hello world"
#ifdef TO_REPLACE
    std::cout<< "defined 2\n";

#else
    std::cout<<"not 2\n";
#endif

std::cout<<TO_REPLACE<<std::endl;
    return 0;
}
