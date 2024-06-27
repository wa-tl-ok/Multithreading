#include <iostream>
#include <mutex>
#include <thread>

int shared_data = 0;
std::mutex mtx;

void increment_data() {
	for (int i = 0; i < 100000; i++) {
		mtx.lock();
		shared_data++;
		mtx.unlock();
	}
}

int main() {
	std::thread t1(increment_data);
	std::thread t2(increment_data);

	t1.join();
	t2.join();

	std::cout << "Shared data : " << shared_data << '\n';

	return 0;
}
