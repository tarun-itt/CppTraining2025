#include <iostream>


void fun(int&& x){
    std::cout<<"RVALUE\n";
}

int main(){
    int x = 34;
    int y=120;

    int& ref = x;
    std::cout<<x<<"  "<<&ref<<"  "<<&x<<"\n";

    ref = y;

    std::cout<<&y<<"  "<<&ref<<" "<<ref<<" "<<x<<"\n";


    int a = 10;
int b = 20;
int * const ptr = &a;

// *ptr = 15;    // isallowed: can modify the value pointed to
// ptr = &b;     // error: cannot change the pointer address

const int c = 24;
int d =90;
const int& ref2 = c;
const int*  ptr2  =&ref2;

ptr2 = &b;

fun(14);

return 0;
}