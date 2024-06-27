#include <iostream> 
#include <queue> 
#include <mutex> 
#include <condition_variable>
#include <thread>

template<typename T>
class fixed_size_queue {
public:
    explicit fixed_size_queue(size_t max_size) : max_size_(max_size) {}

    void Push(const T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        not_full_.wait(lock, [this] { return queue_.size() < max_size_; });
        queue_.push(item);
        not_empty_.notify_one();
    }

    T Pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        not_empty_.wait(lock, [this] { return !queue_.empty(); });
        T item = queue_.front();
        queue_.pop();
        not_full_.notify_one();
        return item;
    }

private:
    std::queue<T> queue_;
    size_t max_size_;
    std::mutex mutex_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
};

int main() {
    fixed_size_queue<int> queue(5);

    std::thread producer([&queue]() {
        for (int i = 1; i <= 10; ++i) {
            queue.Push(i);
            std::cout << "Produced: " << i << std::endl;
        }
        });

    std::thread consumer([&queue]() {
        for (int i = 1; i <= 5; ++i) {
            int item = queue.Pop();
            std::cout << "Consumed: " << item << std::endl;
        }
        });

    producer.join();
    consumer.join();

    return 0;
}
