#include <iostream>
class B{};
class A{
public:
    int r = 10;
    double operator++(int k){
        int a =13;
        a +=10;
        return a;
    }
    
    A operator+ (int val){
        r += val;
        return *this;
    }
friend std::ostream& operator<<(std::ostream& os, const A& obj) ;
};

std::ostream& operator<<(std::ostream& os, const A& obj) {
        os << obj.r;
        return os;
    }

int main(){
    A a;

   std::cout<<(a+10);
    return 0;
}