#include <chrono>
#include <iostream>
#include <thread>

#include "Input/FileInputReader.h"
#include "Utils/InputValidation.h"

FileInputReader::FileInputReader(const std::string &filePath,
                                 IBlockingQueue<InputRequest> *queue,
                                 const ElevatorSystemConfig &config,
                                 MessageSender *messageSender)
    : filePath(filePath), running(false), requests(queue), messageSender(messageSender), config(config) {}

FileInputReader::~FileInputReader() {
    stop();
}

void FileInputReader::start() {
    if (running.load()) {
        messageSender->sendWarning("FileInputReader is already running");
        return;
    }
    
    fileStream.open(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        messageSender->sendError("Failed to open or create file for reading: " + filePath);
        return;
    }

    running.store(true);
    readerThread = std::thread(&FileInputReader::readLoop, this);
}

void FileInputReader::stop() {
    if (!running.load()) {
        messageSender->sendWarning("FileInputReader is already not running.");
        return;
    }

    running.store(false);
    if (readerThread.joinable()) {
        readerThread.join();
    }

    if (fileStream.is_open()) {
        fileStream.close();
    }
}

bool FileInputReader::isRunning() const {
    return running.load();
}

void FileInputReader::readLoop() {
  fileStream.seekg(0, std::ios::end);
  
  while (isRunning()) {
      std::streampos pos = fileStream.tellg();
      std::string line;
      
      if (std::getline(fileStream, line)) {
          if (!fileStream.eof()) {
              if (!line.empty()) {
                  processLine(line);
              }
          } else {
              fileStream.clear();
              fileStream.seekg(pos);
              std::this_thread::sleep_for(std::chrono::milliseconds(200));
          }
      } else {
          fileStream.clear();
          fileStream.seekg(pos);
          std::this_thread::sleep_for(std::chrono::milliseconds(200));
      }
  }
}

void FileInputReader::processLine(const std::string &line) {
    if (line.empty()) {
        return;
    }

    InputValidation::ValidationResult result = InputValidation::validate(line, config);

    if (result.isValid) {
        if(requests) {
            requests->push(result.request);
        }
    } else {
        if (messageSender) {
            messageSender->sendError(result.errorMessage);
        }
    }
}