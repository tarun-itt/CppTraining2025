#include <iostream>
#include <string>

class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() {
        std::cout << "Shape Destructor Called" << std::endl;
    }
};

class Color {
public:
    virtual void fillColor() const {
        std::cout << "Filling color" << std::endl;
    }
    virtual ~Color() {
        std::cout << "Color Destructor Called" << std::endl;
    }
};

class Texture {
public:
    virtual void applyTexture() const {
        std::cout << "Applying texture" << std::endl;
    }
    virtual ~Texture() {
        std::cout << "Texture Destructor Called" << std::endl;
    }
};

class ColoredTexturedShape : public virtual Color, public virtual Texture, public virtual Shape {
public:
    ColoredTexturedShape() {
        std::cout << "ColoredTexturedShape Constructor Called" << std::endl;
    }

    void draw() const override {
        std::cout << "Drawing a colored and textured shape." << std::endl;
    }

    void fillColor() const override {
        std::cout << "Filling with custom color!" << std::endl;
    }

    void applyTexture() const override {
        std::cout << "Applying custom texture!" << std::endl;
    }

    virtual ~ColoredTexturedShape() {
        std::cout << "ColoredTexturedShape Destructor Called" << std::endl;
    }
};

int main() {
    Shape* shape = new ColoredTexturedShape();
    shape->draw();
    dynamic_cast<ColoredTexturedShape*>(shape)->fillColor();
    dynamic_cast<ColoredTexturedShape*>(shape)->applyTexture();
    
    delete shape;

    return 0;
}
