#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "concurrent_queue_cv.h"
#include <atomic>
#include <thread>
#include <functional>

using func = std::function<void()>;

class thread_pool {
	concurrent_queue_cv<func> work_queue;
	std::vector<std::thread> v;
	void worker();
public:
	thread_pool();
	~thread_pool();
	void submit(func f);
};

#endif //THREAD_POOL_H