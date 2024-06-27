#include <iostream>
#include <future>

int calc_sum(int a, int b) {
	return a + b;
}

int main() {
	std::promise<int> sum_promise;
	std::future<int> sum_future = sum_promise.get_future();

	std::thread sum_thread([&sum_promise]() {
		int result = calc_sum(2, 3);
		sum_promise.set_value(result);
	});

	int sum = sum_future.get();
	std::cout << "Sum : " << sum << '\n';

	sum_thread.join();

	return 0;
}
