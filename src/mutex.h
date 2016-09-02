//-*-C++-*-
#pragma once

#include <mutex>

/*
 * This seems like a function name because it's meant to be used like a function
 * It's a class because it can take advantage of RAII
 */
class acquire {
public:
	acquire(std::mutex &lock) {
		this->lock = lock;
		lock.lock();
	}
	~acquire() {
		lock.unlock();
	}
private:
	std::mutex &lock;
};
