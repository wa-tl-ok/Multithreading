#include <iostream>
#include <thread>
#include <mutex>

class Semaphore {
public:
	Semaphore(int n) : count_(n) {}

	void Leave() {
		std::unique_lock<std::mutex> guard(mutex_);
		cv_.notify_one();
		++count_;
	}

	void Enter() {
		std::unique_lock<std::mutex> guard(mutex_);
		cv_.wait(guard, [this] { return count_ > 0; });
		--count_;
	}

private:
	int count_;
	std::mutex mutex_;
	std::condition_variable cv_;
};
