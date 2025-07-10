#include <iostream>

bool fun(){
    // demo 
    return 0;
}

int x = 5;
int& getRef() { return x; }

decltype(auto) foo() { return getRef(); } // returns int&


int main(){
    auto x = 3.4;
    auto y = 34;
    auto z = "ereiesler";
    auto ptr = &x;

    std::cout<<typeid(x).name()<<"\n";
    std::cout<<typeid(y).name()<<"\n";
    std::cout<<typeid(z).name()<<"\n";
    std::cout<<typeid(ptr).name()<<"\n\n";

    //decltype
    decltype(fun()) d1;
    decltype(x) d2 = 1.0+4.3;
    decltype((x)) d3 = x;


        int array[5] = { 1, 2, 3, 4, 5 };
    int size = sizeof(array);

    std::cout<<"The size of the array is: "<<size<<"\n";
    std::cout.flush(); //flushes the input buffer, similar to using endl, \n + flush

    std::cout<<d3<<" "<<&x<<"\n";
    std::cout<<typeid(d1).name()<<"\n";
    std::cout<<typeid(d2).name()<<"\n";
    std::cout<<typeid(decltype(fun())).name()<<"\n";
    return 0;
}