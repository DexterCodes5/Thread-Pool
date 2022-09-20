#include "thread_pool.h"
#include <algorithm>

thread_pool::thread_pool() {
	const unsigned thread_count = std::thread::hardware_concurrency();
	for (unsigned i = 0; i < thread_count; i++)
		v.emplace_back(&thread_pool::worker, this);
}

thread_pool::~thread_pool() {
	std::for_each(v.begin(), v.end(), [](auto& v) {v.join(); });
}

void thread_pool::worker() {
	while (true) {
		func task;
		work_queue.pop(task);
		task();
	}
}

void thread_pool::submit(func f) {
	work_queue.push(f);
}