#include <iostream>
using namespace std;

class Test {
private:

    Test() {
        cout << "Default constructor\n";
    }
public:
    int value;
    // Public copy constructor
    Test(const Test& other) {
        cout << "Copy constructor\n";
        value = other.value;
    }


    static Test create(int v) {
        Test t;     
        t.value = v;
        return t;
    }
};

int main() {
    Test t1 = Test::create(10);
    Test t2 = t1;   
    t1.value = 1356;          
    cout << "t2.value = " << t2.value << endl;
    return 0;
}
