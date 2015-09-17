#ifndef TREK_NET_SESSION_HPP
#define TREK_NET_SESSION_HPP

#include "controller.hpp"

#include <trek/common/callback.hpp>

#include <boost/asio/ip/tcp.hpp>

#include <string>
#include <array>
#include <unordered_map>

namespace trek {
namespace net {

class Session : public std::enable_shared_from_this<Session> {
    using SessionPtr = std::shared_ptr< Session >;

    using ControllerPtr = std::shared_ptr<Controller>;
    using ControllerMap = std::unordered_map<std::string, ControllerPtr>;
public:
    using DestroyCallback = Callback< void(const SessionPtr&)>;
    using MessageCallback = Callback< void(const Session&, const std::string message) >;
    using StatusCallback = Callback< void(const Session&) >;
    using TCP = boost::asio::ip::tcp;
public:
    Session(const ControllerMap& controllers, TCP::socket&& socket);
    void run();
    std::string getRemoteAddress() const;

public: //callbacks
    const MessageCallback& onRecv();
    const MessageCallback& onSend();

    const StatusCallback& onStart();
    const StatusCallback& onClose();
    const DestroyCallback& onDestroy();
protected:
    void recv();
    void send(const std::string& response);
    Controller& getController(const std::string& request);
private:
    ControllerMap mControllers;
    TCP::socket mSocket;

    MessageCallback mOnRecv;
    MessageCallback mOnSend;

    StatusCallback mOnStart;
    StatusCallback mOnClose;
    DestroyCallback mOnDestroy;
    std::array<char, 65527> mBuffer;
};

} //net
} //trek


#endif // TREK_NET_SESSION_HPP
