#pragma once

#include <trek/net/controller.hpp>
#include <trek/net/session.hpp>
#include <trek/net/multicastsender.hpp>

#include <string>
#include <cstdint>
#include <unordered_set>

namespace trek {
namespace net {

class Server {
    using SessionPtr = std::shared_ptr<Session>;
    using SessionSet = std::unordered_set<SessionPtr>;
    using ControllerPtr = std::shared_ptr<Controller>;
    using Controllers   = std::unordered_map<std::string, ControllerPtr>;

    using StatusCallback = Callback<void(const Server&)>;

    using IoService = boost::asio::io_service;
    using IpAddress = boost::asio::ip::address;
    using TCP = boost::asio::ip::tcp;
public:
    struct Conifg {
        std::string ip;
        uint16_t port;

        std::string multicastIp;
        uint16_t multicastPort;
    };
    Server(const std::vector<ControllerPtr>& controllers, const Conifg& conf);
    ~Server();
    void run();
    void stop();

    const Session::MessageCallback& onRecv();
    const Session::MessageCallback& onSend();
    const Session::StatusCallback& onSessionStart();
    const Session::StatusCallback& onSessionClose();

    const StatusCallback& onStart();
    const StatusCallback& onStop();

protected:
    void doAccept();
    void addSession(const SessionPtr& session);
    void removeSession(const SessionPtr& session);
    Controllers convertControllers(const std::vector<ControllerPtr>& controllers);
private:
    Controllers mControllers;
    IoService mIoService;
    TCP::acceptor mAcceptor;
    TCP::socket mSocket;
    MulticastSender mSender;

    Session::MessageCallback mOnRecv;
    Session::MessageCallback mOnSend;
    Session::StatusCallback  mOnSessionStart;
    Session::StatusCallback  mOnSessionClose;

    StatusCallback mOnStart;
    StatusCallback mOnStop;
    SessionSet   mSessions;
};

} //net
} //trek
