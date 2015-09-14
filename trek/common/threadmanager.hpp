#ifndef TREK_COMMON_THREAD_MANAGER_HPP
#define TREK_COMMON_THREAD_MANAGER_HPP

#include <thread>
#include <memory>

namespace trek {

class ThreadManager {
    using Function = std::function<void()>;
    using ThreadPtr = std::unique_ptr< std::thread >;
public:
    ~ThreadManager();
    void run(const Function& func);
    void join();

    operator bool() const;
private:
    ThreadPtr mThread;
};


}

#endif // TREK_COMMON_THREAD_MANAGER_HPP
