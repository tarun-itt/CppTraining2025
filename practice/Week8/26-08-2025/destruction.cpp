#include <iostream>
#include <exception>
#include <stdexcept>

class A {
    public:

        A () {
            std::cout<<"A constructed\n";
        }

        ~A(){
            std::cout<<"A Destroyed \n";
        }
};

class B {
    public:

        B () {
            std::cout<<"B constructed\n";
        }

        ~B(){
            std::cout<<"B Destroyed \n";
        }
};

class C {
    public:

        C () {
            std::cout<<"C constructed\n";
        }

        ~C(){
            std::cout<<"C Destroyed \n";
        }
};

void fun2(){    
    B b;
    C c;
    A a;
    std::cout<<"\n";

    throw std::exception();
        std::cout<<"fun 2 ends\n";


}

void fun(){
        C a;
    B b;

fun2();


    std::cout<<"End of fun method\n";

}
int main(){
    A a;
    B b;
    C c;
    std::cout<<"\n";


        std::cout<<"\n";
        try{
       fun();
    }catch(std::exception e){std::cout<<"error detected\n";}

    std::cout<<"main end\n";
    return 0;

}