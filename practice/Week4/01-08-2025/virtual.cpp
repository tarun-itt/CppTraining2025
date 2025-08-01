#include <iostream>
#include <vector>

class Shape {
    int a=10;
    int b=20;

public:
Shape(){std::cout<<"Shape const called\n";}
    virtual void draw(){
        std::cout << "shape\n";
    }
    void fill(){
        std::cout<<"Color filled for shape\n";
    }
    virtual ~Shape() = default; 
};

class Circle : public Shape {
    int c=30;
public:

    void draw()  override { 
        std::cout << "circle\n";
    }
    void fill(){
        std::cout<<"Color filled for Circle\n";
    }
};

class Square : public Shape {
public:
    void draw() override {
        std::cout << "Square\n";
    }
        void fill(){
        std::cout<<"Color filled for square\n";
    }
};

int main() {
    std::vector<Shape*> shapes = {new Circle(), new Square(), new Shape()};

    for (auto* shape : shapes) {
        shape->draw();
        shape->fill();
        std::cout<<"Size: "<<sizeof(*shape)<<"\n\n";
    }

    for (auto* shape : shapes) {
        delete shape;
    }
}
