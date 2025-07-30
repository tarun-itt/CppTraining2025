#include <iostream>

class Simple{
    public:
    int a;
    int b;
    Simple() = default;
};
int main(){
Simple s ;//= new Simple();
int* ptr = &s.a;
//std::cout<<s->a<<"  "<<s->b<<"\n";
std::cout<<s.a<<"  "<<s.b<<"\n";
std::cout<<*ptr<<std::endl;
    return 0;
}