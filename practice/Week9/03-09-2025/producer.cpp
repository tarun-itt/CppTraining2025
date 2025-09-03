#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

const unsigned int MAX_BUFFER_SIZE = 5;
std::queue<int> buffer;

std::mutex mtx;
std::condition_variable cv_producer;
std::condition_variable cv_consumer;

bool done = false;

void producer(int id, int items) {
    for (int i = 1; i <= items; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_producer.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; });

        buffer.push(i);
        std::cout << "Producer " << id << " produced: " << i << "\n";

        lock.unlock();
        cv_consumer.notify_one();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }
    cv_consumer.notify_all();
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_consumer.wait(lock, [] { return !buffer.empty() || done; });

        if (!buffer.empty()) {
            int item = buffer.front();
            buffer.pop();
            std::cout << "\tConsumer " << id << " consumed: " << item << "\n";

            lock.unlock();
            cv_producer.notify_one();

            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        } else if (done) {
            break;
        }
    }
}

int main() {
    std::thread p1(producer, 1, 10);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);

    p1.join();
    c1.join();
    c2.join();

    return 0;
}
