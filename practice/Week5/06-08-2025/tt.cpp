#include <cstdio>
#include <iostream>
class A{
  public:

  int a = 34;
  int b = this->a;
};

int main()
{
  A a;
  std::cout<<a.b;
}