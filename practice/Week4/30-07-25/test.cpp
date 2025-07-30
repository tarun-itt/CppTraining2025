#pragma pack(1)
#include <iostream>
class A {
public:
  A(int val) : value(34.2),constVar(val) {
    int data = 10;
    ch = 'h';
  }

private:
  int data = 99;
  double value;
  static const int constVar ;
  char ch;
};

 //int A::constVar =34;

int main() {
    int val;
    std::cin>>val;
    A a(val);
std::cout<<sizeof(a);
  return 0;
}