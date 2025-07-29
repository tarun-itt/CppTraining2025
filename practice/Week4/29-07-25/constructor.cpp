#include <iostream>
using namespace std;

class Box {
    int length, width, height;
    static int testVar;
    const int constVar = 100;
public:

    Box(){
        length = width = height = 1;
    }


    Box(int l, int w, int h):length(l),width(w),height(h) {
    }

    Box(int l, int w) {
        length = l;
        width = w;
        height = 1; 
    }

    Box(const Box& other) {
        length = other.length;
        width = other.width;
        height = other.height;
    }

    void print() const {
        cout << "Box: " << length << " x " << width << " x " << height << endl;
    }
};

int Box::testVar = 10;

int main() {
    Box b1;                 
    Box b2(2, 3, 4);        
    Box b3(5, 6);           
    Box b4 = b2;

    b1.print();
    b2.print();
    b3.print();
    b4.print();

    return 0;
}
