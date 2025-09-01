#include <iostream>
//we cant use non static local variable like abc, in the class, because class object may outlive scope of the function itself, but we can use asd as it global,
int asd = 234;


// void fun(){
//     int abc = 234;
//     class A{
//         public:
//         int k;
//         A():k(23){} 
//         A(const A& obj):k(obj.k){std::cout<<"Copy constructor called";}
//     };
//     A oo;
// }



// int main()
// {
//    fun();

//     return 0;
// }

struct MyLocal {
    int x;

    MyLocal(int v) : x(v) {}
    MyLocal(const MyLocal& obj):x(obj.x){std::cout<<"Copy const called\n";}
    MyLocal(MyLocal&& obj) noexcept: x(obj.x){std::cout<<"Move called\n";}
};

MyLocal createLocal() {
    int usi = 2334;
    struct funLocal: public MyLocal {
        funLocal(int a):MyLocal(a){std::cout<<"Fun local  called\n";}
    };
    funLocal obj(23);
    return obj;   
}

int main() {
    MyLocal m = createLocal();
    std::cout << m.x;      
}
