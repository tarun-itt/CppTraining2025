#include <thread>
#include <chrono>

#include "Timer.h"

void Timer::sleep(int duration){
    std::this_thread::sleep_for(std::chrono::seconds(duration));
}