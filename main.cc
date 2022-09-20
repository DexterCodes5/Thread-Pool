#include <iostream>
#include <mutex>
#include "thread_pool.h"
using namespace std::literals;

std::mutex mx;

void task() {
	std::lock_guard<std::mutex> lk(mx);
	std::cout << "Thread ID" << std::this_thread::get_id() << " started" << std::endl;
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread ID" << std::this_thread::get_id() << " finished" << std::endl;
}

int main() {
	std::cout << "Thread pool with " << std::thread::hardware_concurrency() << " threads" << std::endl;
	thread_pool pool;
	
	for (unsigned i = 0; i < 20; i++)
		pool.submit(task);
	
	std::this_thread::sleep_for(5s);
}