#pragma once

#include <mutex>
#include <memory>
#include <vector>

namespace trek {
namespace net {

class MulticastReceiver {
    class impl;
public:
    MulticastReceiver(const std::string& addr, uint16_t port);
    ~MulticastReceiver();
    void run();
    void stop();
    void onRecv(const std::function<void(std::vector<char>&)>& callback);
private:
    std::unique_ptr<impl> mImpl;
};

} //net
} //trek
