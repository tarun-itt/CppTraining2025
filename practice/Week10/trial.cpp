#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <semaphore.h>


void fun(sem_t* sem){
    sem_wait(sem);
   std::cout<<"Running thread: "<< std::this_thread::get_id()<<"\n";

   std::this_thread::sleep_for(std::chrono::seconds(5));
   sem_post(sem);
}

void fun2(std::mutex &_mutex){
    _mutex.lock();
    std::cout<<"Running thread: "<< std::this_thread::get_id()<<"\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout<<"closed::\n\n";
    _mutex.unlock();

}

void fun3(std::mutex &_mutex){
    _mutex.unlock();
   std::cout<<"::Running thread: "<< std::this_thread::get_id()<<"\n";
   // _mutex.unlock();
}

int main(){
    sem_t semaphore;
    sem_init(&semaphore,0,1);

    std::mutex _mutex;

    std::thread t1(fun2, std::ref(_mutex));
        std::thread t2(fun3,std::ref( _mutex));
    std::thread t3(fun2, std::ref(_mutex));


    t1.join();
    t2.join();
    t3.join();

    return 0;
}