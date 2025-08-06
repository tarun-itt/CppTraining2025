#include <iostream> 
using namespace std; 

class A { 
public: 
	void show() 
	{ 
		cout << "Hello from A \n"; 
	} 
}; 

class B : virtual public A { 
    // void show(){
    //     cout<<"hello from b";
    // }
}; 

class C : virtual public A { 
    // void show(){
    // cout<<"hello from c";
    // }
}; 

class D : public B, public C { 
}; 

int main() 
{ 
	D object; 
	object.show(); 
}