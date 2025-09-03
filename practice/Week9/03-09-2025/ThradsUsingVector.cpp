#include <iostream>
#include <ostream>
#include <vector>
#include <thread>
#include <mutex>

std::vector<int> globalVector;
std::mutex mtx;

void pushToVector(int val) {
    std::lock_guard<std::mutex> lock(mtx);
    globalVector.push_back(val);
}

int main(){
    std::thread t1(pushToVector,89);
    std::thread t2(pushToVector,6712);

    t1.join();
    t2.join();

    for(auto& v: globalVector){
        std::cout<<v<<" "<<std::endl;
    }

    return 0;
}