#include <chrono>
#include <iostream>
#include <thread>

int semaphore = 0;

void helperFun(){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<<"Helper method completed...";
    semaphore = 1;
}
int main(){
    std::thread helperThread(helperFun);
    helperThread.detach();
    std::cout<<"Main continues... \n";

    while(!semaphore);
    return 0;
}   