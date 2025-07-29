#include <cassert>
#include <iostream>

class Rectangle {
private:
  int height;
  int width;
  
  void checkInvariant() {
    assert(height >= 0 && height >= width);
    assert(width >= 0);
  }

public:

  Rectangle(int height, int width){
    this->height = height;
    this->width = width;
    checkInvariant();
  }
};

int main(){
  Rectangle rectangle(20,10);
  Rectangle rectangleB(14, 20);

  return 0;
}
