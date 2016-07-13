#pragma once

#include <memory>
#include <string>
#include <cstdint>

namespace trek {
namespace net {

class MulticastSender {
    class impl;
public:
    MulticastSender(const std::string& addr, uint16_t port);
    ~MulticastSender();
    void send(const std::string& response);
private:
    std::unique_ptr<impl> mImpl;
};

} //net
} //trek
