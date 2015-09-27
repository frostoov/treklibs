#include "threadmanager.hpp"

#include "assertion.hpp"

namespace trek {

using std::thread;
using std::make_unique;

ThreadManager::~ThreadManager() {
    if(mThread != nullptr && mThread->joinable())
        mThread->join();
}

void ThreadManager::run(const Function& func) {
    if(mThread == nullptr)
        mThread = make_unique<thread>(func);
    else
        throw Assertion("ThreadManager::run: thread is already running");
}

void ThreadManager::join() {
    mThread->join();
    mThread.reset();
}

ThreadManager::operator bool() const {
    return mThread != nullptr;
}

}


