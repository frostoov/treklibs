#include "multicastsender.hpp"

#include <boost/asio/ip/udp.hpp>
#include <boost/asio/io_service.hpp>

namespace trek {
namespace net {

namespace asio = boost::asio;

using std::string;
using std::make_unique;

class MulticastSender::impl {
public:
    impl(const string& addr, uint16_t port)
        : mEndpoint(asio::ip::address::from_string(addr), port),
          mSocket(mIoService, mEndpoint.protocol()) { }
    void send(const string& msg) {
        mSocket.send_to(asio::buffer(msg), mEndpoint);
    }
private:
    asio::io_service mIoService;
    asio::ip::udp::endpoint  mEndpoint;
    asio::ip::udp::socket mSocket;

    asio::ip::address mMulticastAddress;
};
    

MulticastSender::MulticastSender(const string& addr, uint16_t port)
    : mImpl(make_unique<impl>(addr, port)) { }

MulticastSender::~MulticastSender() { }

void MulticastSender::send(const string& msg) {
    mImpl->send(msg);
}

}
}
