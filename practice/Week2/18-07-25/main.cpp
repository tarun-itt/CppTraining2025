#include "mathLib.h"
#include "printLib.h"
#include <dlfcn.h>

int main(){
    std::cout<<"Sum: "<<add(2,5)<<std::endl;
    std::cout<<"Sub: "<<add(10,1)<<std::endl;
    printGreet("Tarun");
    printJaipur();

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