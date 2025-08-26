#include <iostream>
#include <exception>

int  *arr;


class A {
    public:
    A() {
        std::cout<<"A contructed\n";
    }

    ~A(){
        std::cout<<"A destroyed\n";
    }
};

A  *obj;

void cleanup(){
  //  delete[] arr;
    delete obj;
}

int main(){
    std::set_terminate(cleanup);
    // int* arr = new int A* obj = new A();[10];
    // A* obj = new A();
  //  arr = new int[10];
    obj = new A();

    std::cout<<"About to throw an exception\n\n";
    throw std::exception(); // mocked an unknown exception

    // delete[] arr;
    // delete obj;

    return 0;
}