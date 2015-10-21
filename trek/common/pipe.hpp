#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace trek {

template<typename T>
class Pipe {
	using Queue = std::queue<T>;
	using Mutex = std::mutex;
	using Lock  = std::unique_lock<Mutex>;
public:
	Pipe()
		: mActive(true) { }

	auto send(const T& item) {
		if(!mActive.load())
			return false;
		Lock lock(mMutex);
		mQueue.push(item);
		mCv.notify_one();
		return true;
	}

	auto recv(T& item) {
		if(*this == false)
			return false;

		Lock lock(mMutex);

		while(mQueue.empty() && mActive.load())
			mCv.wait(lock);
		if(mQueue.empty())
			return false;
		item = mQueue.front();
		mQueue.pop();
		return true;
	}

	operator bool() const {
		return mActive.load() || !mQueue.empty();
	}

	auto close() {
		mActive.store(false);
		mCv.notify_all();
	}

	auto empty() const {
		return mQueue.empty();
	}

private:
	Queue mQueue;
	Mutex mMutex;
	std::condition_variable mCv;
	std::atomic_bool mActive;
};

} //trek