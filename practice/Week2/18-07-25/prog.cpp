#include <dlfcn.h>
#include <iostream>

int main(){

    void* handle = dlopen("./libprintLib2.so", RTLD_LAZY);
    if (!handle)
    {
        std::cout << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }
    void (*printPhone)() = (void (*)())dlsym(handle,"printPhone");
    void (*printLap)() = (void(*)())dlsym(handle,"printLap");
    
    printPhone();
    printLap();
    dlclose(handle);
    return 0;
}