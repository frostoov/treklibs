#include "multicastreceiver.hpp"

#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/multicast.hpp>

namespace trek {
namespace net {

namespace asio = boost::asio;

using std::vector;
using std::make_unique;
using std::mutex;
using std::unique_lock;
using std::function;
using std::string;

using boost::system::error_code;

class MulticastReceiver::impl {
public:
    impl(const string& addr, uint16_t port) 
        : mSocket(mIoService),
          mEndpoint(asio::ip::udp::v4(), port),
          mMulticastAddress(asio::ip::address::from_string(addr)),
          mBuffer(mBufferSize),
          mCallback(nullptr) {
        mSocket.open(asio::ip::udp::v4());
        mSocket.bind(mEndpoint);

        joinMulticastGroup(mMulticastAddress);
    }
    
    ~impl() {
        stop();
    }
    
    void run() {
        mIoService.reset();
        doReceive();
        mIoService.run();
    }
    
    void stop() {
        mIoService.stop();
    }
    
    void onRecv(const function<void(vector<char>&)>& cb) {
        mCallback = cb;
    }
protected:
    void doReceive() {
        mBuffer.resize(mBufferSize);
        mSocket.async_receive_from(boost::asio::buffer(mBuffer), mEndpoint, [this](auto& error, auto size) {
            if(!error) {
                mBuffer.resize(size);
                mCallback(mBuffer);
            }
            doReceive();
        });
    }

    void joinMulticastGroup(const asio::ip::address& addr) {
        mSocket.set_option(asio::ip::multicast::join_group(addr));
    }

    void leaveMulticastGroup(const asio::ip::address& addr) {
        mSocket.set_option(asio::ip::multicast::leave_group(addr));
    }
private:
    asio::io_service mIoService;
    asio::ip::udp::socket mSocket;
    asio::ip::udp::endpoint mEndpoint;
    asio::ip::address mMulticastAddress;

    mutex callbackMutex;
    vector<char> mBuffer;
    function<void(vector<char>&)> mCallback;

    static constexpr size_t mBufferSize = 65527;
};

MulticastReceiver::MulticastReceiver(const string& addr, uint16_t port)
    : mImpl(make_unique<impl>(addr, port)) { }

MulticastReceiver::~MulticastReceiver() { }

void MulticastReceiver::run() {
    mImpl->run();
}

void MulticastReceiver::stop() {
    mImpl->stop();
}

void MulticastReceiver::onRecv(const function<void(vector<char>&)>& callback) {
    mImpl->onRecv(callback);
}

} //net
} //trek
