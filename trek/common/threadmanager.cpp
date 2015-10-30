#include "threadmanager.hpp"

namespace trek {

using std::thread;
using std::make_unique;
using std::logic_error;

ThreadManager::~ThreadManager() {
	if(mThread != nullptr && mThread->joinable())
		mThread->join();
}

void ThreadManager::run(Function&& func) {
	if(mThread != nullptr)
		throw logic_error("ThreadManager::run: thread is already running");
	mThread = make_unique<thread>(func);	
}

void ThreadManager::join() {
	mThread->join();
	mThread.reset();
}

ThreadManager::operator bool() const {
	return mThread != nullptr;
}

}


