#pragma once

#include "request.hpp"
#include "response.hpp"

#include <trek/common/threadmanager.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/address.hpp>

#include <array>

namespace trek {
namespace net {

class Client {
    using IpAddress = boost::asio::ip::address;
    using IoService = boost::asio::io_service;
    using TCP = boost::asio::ip::tcp;
public:
    Client(const std::string& ip, uint16_t port);
    Response sendRequst(const Request& request);
private:
    IoService   mIoService;
    TCP::socket mSocket;

    std::array<char, 65527> mBuffer;
};

}
}

