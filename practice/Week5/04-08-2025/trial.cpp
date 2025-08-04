#include <iostream>

class Alpha;

class Beta {
private:
    int b;
public:
    Beta(int val) : b(val) {}
    friend void access(const Alpha&, const Beta&);
};

class Alpha {
private:
    int a;
public:
    Alpha(int val) : a(val) {}
    friend void access(const Alpha&, const Beta&);
};

void access(const Alpha& x, const Beta& y) {
    std::cout << x.a + y.b << std::endl;
}

int main() {
    Alpha a(10);
    Beta b(25);
    access(a, b);
}
