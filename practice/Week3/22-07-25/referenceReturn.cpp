#include <iostream>

struct point{
    int x;
    int y;

    point& fun1(){
        std::cout<<"Hello";
        return *this;
    }
    point& fun2(){
        std::cout<<"World";
        return *this;
    }
};

point& getPoint(){
    //point p{23,98}; //returning a refrence to a local object, results in undefined behavior, as scope of object ends with the function
    static point p{35,12}; //this works, because we declared static, and object's life extended to scope of the program

     return p;
}


int main(){
    getPoint().fun1().fun2();
    return 0;
}