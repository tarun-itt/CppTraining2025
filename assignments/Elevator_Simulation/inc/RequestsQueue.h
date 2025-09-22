#ifndef REQUESTS_QUEUE_H
#define REQUESTS_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

#include "IBlockingQueue.h"

template <typename T>
class RequestsQueue : public IBlockingQueue<T> {
public:
    RequestsQueue() : m_shutdown(false) {}

    void push(const T& item) override {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_shutdown) {
                return;
            }
            m_queue.push(item);
        }
        m_condition.notify_one();
    }

    T try_pop() override {
        std::lock_guard<std::mutex> lock(m_mutex);
        
        if (m_queue.empty()) {
            return T();
        }
        
        T item = std::move(m_queue.front());
        m_queue.pop();
        return item;
    }

    bool empty() const override {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    size_t size() const override {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    void shutdown() override {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_shutdown = true;
        }
        m_condition.notify_all();
    }

private:
    std::queue<T> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_condition;
    bool m_shutdown;
};

#endif