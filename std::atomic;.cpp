#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> atomic_data(0);

void increment_data() {
	for (int i = 0; i < 10000; i++) {
		atomic_data.fetch_add(i, std::memory_order_relaxed);
	}
}

void decrement_data() {
	for (int i = 0; i < 10000; i++) {
		atomic_data.fetch_sub(i, std::memory_order_relaxed);
	}
}

int main() {
	std::thread t1(increment_data);
	std::thread t2(decrement_data);

	t1.join();
	t2.join();

	std::cout << "Atomic data : " << atomic_data << '\n';

	return 0;
}
