#include <chrono>
#include <iostream>
#include <thread>

#include "FileInputReader.h"
#include "InputValidation.h"

FileInputReader::FileInputReader(const std::string &filePath,
                                 IBlockingQueue<InputRequest> *queue,
                                 const ElevatorSystemConfig &config,
                                 MessageSender *messageSender)
    : filePath(filePath), running(false), requests(queue), messageSender(messageSender), config(config), callback(nullptr) {}

FileInputReader::~FileInputReader() {
    stop();
}

void FileInputReader::start() {
    if (running.load()) {
        std::cerr << "FileInputReader is already running" << std::endl;
        return;
    }
    
    fileStream.open(filePath, std::ios::in | std::ios::out | std::ios::trunc);

    if (!fileStream.is_open()) {
        std::cerr << "Failed to open or create file for reading: " << filePath << std::endl;
        return;
    }

    running.store(true);
    readerThread = std::thread(&FileInputReader::readLoop, this);
}

void FileInputReader::stop() {
    if (!running.load()) {
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

void FileInputReader::setRequestCallback(
    std::function<void(const InputRequest &)> cb) {
    callback = cb;
}

bool FileInputReader::isRunning() const {
    return running.load();
}

void FileInputReader::readLoop() {
  fileStream.seekg(0, std::ios::end);
  
  while (running.load()) {
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
      } else if (fileStream.eof()) {
          fileStream.clear();
          std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
    auto result = InputValidation::validate(line, config);
    if (result.isValid) {

        if (requests) {
            requests->push(result.request);
        }

        if (callback) {
            callback(result.request);
        }
    } else {
        if (messageSender) {
            messageSender->sendError(result.errorMessage);
        }
    }
}