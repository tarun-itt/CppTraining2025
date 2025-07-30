#include <iostream>
struct User{
    int getPermission(){
        return 2312; 
    }
};

class A {
  A() {};
  ~A() {};
  static A* obj;
  const int validPermission = 2312; //some random number representing permission

public:
  int ap = 100; //just for testing

  static A* createObject(){
    if(!obj)
        obj = new A();
    return obj;
  }


  int destroyObject(User &user) {
    int returnStatus = 0;
    if (user.getPermission() == validPermission) {
      delete obj;
      returnStatus = -1;
    }
    return returnStatus;
  }
};
 A* A::obj = nullptr;

int main() {


  //   A* obj = new A(); //wont work
  A* obj = A::createObject();
  std::cout<<obj->ap;
obj->ap = 23;
  A* obj2 = obj;
  std::cout<<"\n"<<obj<<"  "<<obj2<<"\n";
  std::cout<<"\n"<<obj2->ap<<"\n";

  // delete obj; cant delete

  // A obj; //cant create object on stack as well

  return 0;
}