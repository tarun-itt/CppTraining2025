#ifndef FILE_INPUT_READER_H
#define FILE_INPUT_READER_H

#include <string>
#include <fstream>
#include <atomic>
#include <thread>

#include "IInputReader.h"
#include "IBlockingQueue.h"
#include "ElevatorSystemConfig.h"
#include "MessageSender.h"

class FileInputReader : public IInputReader {
public:
    explicit FileInputReader(const std::string& filePath, IBlockingQueue<InputRequest>* queue, const ElevatorSystemConfig& config, MessageSender* messageSender = nullptr);
    ~FileInputReader();
    
    void start() override;
    void stop() override;
    void setRequestCallback(std::function<void(const InputRequest&)> callback) override;
    bool isRunning() const override;
    
private:
    void readLoop();
    void processLine(const std::string& line);
    
    std::string filePath;
    std::fstream fileStream;
    std::atomic<bool> running;
    std::thread readerThread;
    IBlockingQueue<InputRequest>* requests;
    MessageSender* messageSender;
    ElevatorSystemConfig config;
    
    std::function<void(const InputRequest&)> callback;
};

#endif