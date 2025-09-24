#ifndef REQUESTS_QUEUE_H
#define REQUESTS_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "../Interfaces/IBlockingQueue.h"
#include "Interfaces/IBlockingQueue.h"

template <typename T>
class RequestsQueue : public IBlockingQueue<T> {
public:
    RequestsQueue() : isShutdown(std::atomic<bool>(false)) {}

    void push(const T& item) override {
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (isShutdown.load()) {
                return;
            }
            queue.push(item);
        }
        condition.notify_one();
    }

    T try_pop() override {
        std::lock_guard<std::mutex> lock(mutex);
        
        if (queue.empty()) {
            return T();
        }
        
        T item = std::move(queue.front());
        queue.pop();
        return item;
    }

    bool empty() const override {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

    size_t size() const override {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.size();
        return queue.size();
    }

    void shutdown() override {
        {
            std::lock_guard<std::mutex> lock(mutex);
            isShutdown.store(true);
        }
        condition.notify_all();
    }

private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable condition;
    std::atomic<bool> isShutdown;
};

#endif