#include <iostream>
#include <shared_mutex>
#include <thread>

int shared_data = 0;
std::shared_mutex mtx;

void write_data() {
	std::unique_lock<std::shared_mutex> lock(mtx);
	shared_data++;
	std::cout << "Write data : " << shared_data << '\n';
}

void read_data() {
	std::shared_lock<std::shared_mutex> lock(mtx);
	std::cout << "Read data : " << shared_data << '\n';
}

int main() {
	std::thread t1(read_data);
	std::thread t2(read_data);
	std::thread t3(write_data);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}
