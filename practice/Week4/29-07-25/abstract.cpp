#include <iostream>
#include <cmath>


class Shape {
public:
    virtual double area() const = 0;
    virtual void print() const = 0;     
    virtual ~Shape() {}
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override {
        return M_PI * radius * radius;
    }
    void print() const override {
        std::cout << "Circle with radius " << radius << ", area: " << area() << "\n";
    }
};

class Rectangle : public Shape {
    double length, width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}
    double area() const override {
        return length * width;
    }
    void print() const override {
        std::cout << "Rectangle " << length << " x " << width << ", area: " << area() << "\n";
    }
};

int main() {
    Shape* shapes[2];
    shapes[0] = new Circle(5);
    shapes[1] = new Rectangle(4, 6);

    for(int i = 0; i < 2; i++) {
        shapes[i]->print();
        delete shapes[i];
    }

    return 0;
}
