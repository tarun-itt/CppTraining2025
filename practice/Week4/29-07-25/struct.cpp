#include <iostream>

struct GridPlayer {

private:
  int length;
  int width;

public:
  int len = 84; // just for testing
  GridPlayer(int length, int width) {}

  int getArea() { return length * width; }
};

int main() {
  GridPlayer p(10, 20);
  std::cout << p.len;
  std::cout << p.getArea();
  return 0;
}