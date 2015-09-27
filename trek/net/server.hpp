#pragma once

#include "controller.hpp"
#include "session.hpp"

#include <trek/common/threadmanager.hpp>

#include <string>
#include <cstdint>
#include <unordered_set>


namespace trek {
namespace net {

class Server {
    using SessionPtr = std::shared_ptr<Session>;
    using SessionSet = std::unordered_set<SessionPtr>;

    using ControllerPtr = std::shared_ptr<Controller>;
    using Controllers   = std::vector<ControllerPtr>;
    using ControllerMap = std::unordered_map<std::string, ControllerPtr>;

    using StatusCallback = Callback<void(const Server&)>;

    using IoService = boost::asio::io_service;
    using IpAddress = boost::asio::ip::address;
    using TCP = boost::asio::ip::tcp;
public:
    Server(const Controllers& controllers, const std::string& ipAdrress, uint16_t port);
    ~Server();
    bool run();
    void stop();

    const Session::MessageCallback& onRecv();
    const Session::MessageCallback& onSend();
    const Session::StatusCallback& onSessionStart();
    const Session::StatusCallback& onSessionClose();

    const StatusCallback& onStart();
    const StatusCallback& onStop();

protected:
    static ControllerMap convertControllers(const Controllers& controllers);
    void doAccept();
    void addSession(const SessionPtr& session);
    void removeSession(const SessionPtr& session);
    void receiveNevodSignal();
private:
    ControllerMap mControllers;
    IoService mIoService;
    TCP::acceptor mAcceptor;
    TCP::socket mSocket;

    Session::MessageCallback mOnRecv;
    Session::MessageCallback mOnSend;
    Session::StatusCallback  mOnSessionStart;
    Session::StatusCallback  mOnSessionClose;

    StatusCallback mOnStart;
    StatusCallback mOnStop;
    SessionSet   mSessions;
    ThreadManager mThread;
};

} //net
} //trek
