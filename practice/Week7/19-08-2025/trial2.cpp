#include <iostream>

class Animal {
public:
    virtual void speak() const {  // ✅ Added 'const'
        std::cout << "Animal speaks!" << std::endl;
    }
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    Dog(){}
    Dog(Animal& a){}
    void speak() const override {  // ✅ const + override
        std::cout << "Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Meow!" << std::endl;
    }
};

void makeAnimalSpeak(const Animal& obj) {
    obj.speak(); 
}

int main() {
    Dog dog;
Animal& ref = dog;  // ref refers to the full Dog object
ref.speak();        // Output: "Woof!"
//since ref is of type animal, runtime checks that speak is virtual therefore it calls the function of actual object and not of refernce type, if virtual were not used, it would call Animal::speak

Animal ani = dog; //while assigning a temperory object of dog is craeted,but only the animal
//part of that object is assigned, means slicing happens
ani.speak(); // Ouput: Animal Speaks

    Animal aa;
    Dog dd = static_cast<Dog>(aa); //if Dog didnt have that additional constructor Dog(Animal&) casting wont happen, but
    //since its present that constructor is called, and it crates a dog object from animal
    dd.speak();

    // Dog dog;
    // Cat cat;

    // makeAnimalSpeak(dog);  // Output: Woof!
    // makeAnimalSpeak(cat);  // Output: Meow!

    // Animal* ptr1 = &dog;
    // Animal* ptr2 = &cat;

    // ptr1->speak();  // Woof!
    // ptr2->speak();  // Meow!

    return 0;
}