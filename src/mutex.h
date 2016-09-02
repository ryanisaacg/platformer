#pragma once

#include <mutex>

class Mutex {
	Mutex(std::mutex lock) {
		lock.lock();
	}
	~Mutex() {
		lock.unlock();
	}
};
