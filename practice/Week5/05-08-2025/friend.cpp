#include <iostream>

class A{
    int a=10;
    int b=20;

    public:
    A(){

    }
    friend void access(A a){
        std::cout<<a.a<<" "<<a.b;
    }
};

void access(A a);
void access2(A a){
   // std::cout<<a.a<<" "<<a.b;
}
int main(){
A a = A();
access(A(a));
access2(a);
}