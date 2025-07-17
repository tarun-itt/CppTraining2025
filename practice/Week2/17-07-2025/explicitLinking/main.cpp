#include <iostream>
#include <dlfcn.h>

int main()
{
    void* handle = dlopen("./libmathlib.so", RTLD_LAZY);
    if (!handle)
    {
        std::cout << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }



    int (*addPtr)(int,int) = (int (*)(int,int))dlsym(handle,"add");
    int (*subPtr)(int,int) = (int (*)(int,int))dlsym(handle,"subtract");
    int (*multPtr)(int,int) = (int (*)(int,int))dlsym(handle,"multiply");
    double (*dividePtr)(int,int) = (double (*)(int,int))dlsym(handle,"divide");

    std::cout << "Add: " << addPtr(5, 3) << "\n";
    std::cout << "Subtract: " << subPtr(5, 3) << "\n";
    std::cout << "Multiply: " << multPtr(5, 3) << "\n";
    std::cout << "Divide: " << dividePtr(5, 3) << "\n";

 
    dlclose(handle);



    return 0;
}
