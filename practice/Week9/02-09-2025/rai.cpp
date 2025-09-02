#include <iostream>
#include <thread>
#include <chrono>

void task() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Task executed in thread.\n";
}

int main() {
    std::thread t(task);
    //t.join(); //if not present Aborts
    std::cout << "exiting main without joining.\n";
    return 0;
}