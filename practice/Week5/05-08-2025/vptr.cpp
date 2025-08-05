#include <iostream>
using namespace std;

class Base {
public:
    virtual void foo() {
        cout << "Base::foo\n";
    }

    virtual void bar() {
        cout << "Base::bar\n";
    }
};

class Derived : public Base {
public:
    void foo() override {
        cout << "Derived::foo\n";
    }

    void bar() override {
        cout << "Derived::bar\n";
    }
};

int main() {
    Base* obj = new Derived();
    obj->foo();
    obj->bar();

    delete obj;
}
