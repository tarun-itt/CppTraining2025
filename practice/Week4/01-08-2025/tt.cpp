#include <iostream>
using namespace std;
 
class A
{
private:
    // int a = 4;
    int a = this->c;
    int c = 5;
 
public:
    void getvalue() { cout << a << " " << c << endl; }
};
 
int main()
{
    A a;
    a.getvalue();
    return 0;
}