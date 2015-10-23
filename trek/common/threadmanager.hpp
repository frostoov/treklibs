#pragma once

#include <thread>
#include <memory>

namespace trek {

class ThreadManager {
	using Function = std::function<void()>;
	using ThreadPtr = std::unique_ptr< std::thread >;
public:
	~ThreadManager();
	void run(Function&& func);
	void join();

	operator bool() const;
private:
	ThreadPtr mThread;
};


}