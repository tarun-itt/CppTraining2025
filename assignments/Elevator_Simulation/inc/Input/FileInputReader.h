#ifndef FILE_INPUT_READER_H
#define FILE_INPUT_READER_H

#include <string>
#include <fstream>
#include <atomic>
#include <thread>

#include "Interfaces/IInputReader.h"
#include "Interfaces/IBlockingQueue.h"
#include "Core/ElevatorSystemConfig.h"
#include "Display/MessageSender.h"
#include "Input/InputRequest.h"

class FileInputReader : public IInputReader {
public:
    explicit FileInputReader(const std::string& filePath, IBlockingQueue<InputRequest>* queue, const ElevatorSystemConfig& config, MessageSender* messageSender = nullptr);
    ~FileInputReader();
    
    void start() override;
    void stop() override;
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
};

#endif