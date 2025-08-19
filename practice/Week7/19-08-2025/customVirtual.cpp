#include <iostream>

class Base {
    public:
        void run(){
            std::cout<<"Base run\n";
        }
        struct v_table {
            void (*run)(Base*);
        };

        v_table* v_ptr;

        Base():v_ptr{}

};

class DerivedA: public Base {

};

int main(){
    return 0;
}