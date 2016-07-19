#include "server.hpp"

namespace trek {
namespace net {

using std::runtime_error;
using std::string;
using std::exception;
using std::make_shared;
using std::logic_error;

using boost::asio::ip::address;

Server::Server(const std::vector<ControllerPtr>& controllers, const Conifg& conf)
    : mControllers(convertControllers(controllers)),
      mAcceptor(mIoService, TCP::endpoint(IpAddress::from_string(conf.ip), conf.port)),
      mSocket(mIoService),
      mSender(conf.multicastIp, conf.multicastPort) {
    auto broadcast = [this](const Response& response) {
        try {
            mSender.send(string(response));
        } catch(exception& e) {
            std::cerr << "server multicast failure " << e.what() << std::endl;
        }
    };
    for(auto& c : mControllers) {
        c.second->setBroadCast(broadcast);
    }
}

Server::~Server() {
    stop();
}

void Server::run() {
    mIoService.reset();
    doAccept();
    mOnStart(*this);
    mIoService.run();
}

void Server::stop() {
    mIoService.stop();
    mSessions.clear();
    mOnStop(*this);
}

const Session::MessageCallback& Server::onRecv() {
    return mOnRecv;
}

const Session::MessageCallback& Server::onSend() {
    return mOnSend;
}

const Session::StatusCallback& Server::onSessionStart() {
    return mOnSessionStart;
}

const Session::StatusCallback& Server::onSessionClose() {
    return mOnSessionClose;
}

const Server::StatusCallback& Server::onStart() {
    return mOnStart;
}

const Server::StatusCallback& Server::onStop() {
    return mOnStop;
}

void Server::doAccept() {
    mAcceptor.async_accept(mSocket, [this](const auto & errCode) {
        if(!errCode) {
            auto newSession = make_shared<Session>(mControllers, std::move(mSocket));

            newSession->onDestroy() = [this] (const auto & session) {
                this->removeSession(session);
            };

            newSession->onStart()   = mOnSessionStart;
            newSession->onClose()   = mOnSessionClose;
            newSession->onRecv()    = mOnRecv;
            newSession->onSend()    = mOnSend;

            this->addSession(newSession);
            newSession->run();

            mSocket = TCP::socket(mIoService);
        }
        this->doAccept();
    });
}

void Server::addSession(const SessionPtr& session) {
    if(mSessions.count(session) != 0)
        throw logic_error("Server::addSession: session already exists");
    mSessions.insert(session);
}

void Server::removeSession(const SessionPtr& session) {
    mSessions.erase(session);
}

Server::Controllers Server::convertControllers(const std::vector<ControllerPtr>& controllers) {
    Controllers cs;
    for(auto c : controllers)
        cs.emplace(c->name(), c);
    return cs;
}

} //net
} //trek
