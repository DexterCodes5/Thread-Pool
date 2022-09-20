#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class concurrent_queue_cv {
	std::mutex mx;
	std::queue<T> q;
	std::condition_variable cv;
public:
	concurrent_queue_cv() {}
	void push(T value) {
		std::lock_guard<std::mutex> lk(mx);
		q.push(value);
		cv.notify_one();
	}

	void pop(T& value) {
		std::unique_lock<std::mutex> lk(mx);
		cv.wait(lk, [this] {return !q.empty();});
		value = q.front();
		q.pop();
	}
};