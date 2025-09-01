#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <string>


class LogProcessor {
private:
    std::string filename;
    std::vector<std::string> logs;

public:
    LogProcessor(const std::string& file) : filename(file) {}

    void processLogFile() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        logs.push_back("Processed: " + filename);
        std::cout << "Thread " << std::this_thread::get_id() 
                  << " finished processing " << filename << std::endl;
    }

    void backgroundCleanup() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Background cleanup completed for " << filename << std::endl;
    }

    const std::vector<std::string>& getLogs() const { return logs; }
};

void demonstrateJoinVsDetach() {
    
    LogProcessor processor1("application.log");
    LogProcessor processor2("error.log");
    
    std::thread worker1(&LogProcessor::processLogFile, &processor1);
    std::thread worker2(&LogProcessor::processLogFile, &processor2);
    
    
    worker1.join();
    worker2.join();

}

int main(){
    demonstrateJoinVsDetach();
    return 0;
}