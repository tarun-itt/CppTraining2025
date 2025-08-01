#include <iostream>
#pragma pack(1)
class A{
    public:
    A(){};
    int a=234 ;
    const int b = 30;
    static int c;
    static const int d ;
    int sds = this->d; 
}; 
const int A::d=900;
class B {
    public:

    int b = 90;
    long a = this->b;
};

int A::c = 7245;
int main(){
    A obj;
    int val = obj.d;
    B obj2;
    return 0;
}