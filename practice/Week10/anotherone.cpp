#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m;

void job0()
{
    std::cout << "Locking the mutex.\n";
    m.lock();
}

void job1()
{
    std::cout << "Unlocking a lock, which was not locked by me.\n";
    m.unlock();
}

void job2()
{

    if (m.try_lock())
    {

        std::cout << "IF this prints, that means no ownership.\n";
    }
    else
    {
        std::cout << "yup owner ship is there for mutexes.\n";
    }
}

int main()
{

    std::thread t0(job0);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread t1(job1);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread t2(job2);

    t0.join();
    t1.join();
    t2.join();
}