#include "server.hpp"

namespace trek {
namespace net {

using std::string;
using std::endl;
using std::exception;
using std::make_shared;
using std::thread;
using std::istream;
using std::make_unique;
using std::chrono::system_clock;

using boost::asio::ip::address;

Server::Server(const Controllers& controllers, const string& ipAdrress, uint16_t port)
    : mControllers(convertControllers(controllers)),
      mAcceptor(mIoService, TCP::endpoint(IpAddress::from_string(ipAdrress), port)),
      mSocket(mIoService) { }

Server::~Server() {
    stop();
}

bool Server::run() {
    if(!mThread) {
        mThread.run( [this] {
            doAccept();
            mIoService.run();
        } );
        mOnStart(*this);
        return true;
    } else
        return false;
}

void Server::stop() {
    if(mThread) {
        mIoService.stop();
        mIoService.reset();
        mSessions.clear();
        mThread.join();
        mOnStop(*this);
    }
}

const Session::MessageCallback&Server::onRecv() {
    return mOnRecv;
}

const Session::MessageCallback&Server::onSend(){
    return mOnSend;
}

const Session::StatusCallback&Server::onSessionStart() {
    return mOnSessionStart;
}

const Session::StatusCallback&Server::onSessionClose() {
    return mOnSessionClose;
}

const Server::StatusCallback&Server::onStart() {
    return mOnStart;
}

const Server::StatusCallback&Server::onStop() {
    return mOnStop;
}

Server::ControllerMap Server::convertControllers(const Controllers& controllers) {
    ControllerMap controllerMap;
    for(const auto& c : controllers) {
        controllerMap.insert( {c->getName(), c} );
    }
    return controllerMap;
}

void Server::doAccept() {
    mAcceptor.async_accept(mSocket, [this](const auto& errCode) {
        if(!errCode) {
            auto newSession = make_shared<Session> (mControllers, std::move(mSocket));

            newSession->onDestroy() = [this] (const auto& session) { removeSession(session); };

            newSession->onStart()   = mOnSessionStart;
            newSession->onClose()   = mOnSessionClose;
            newSession->onRecv()    = mOnRecv;
            newSession->onSend()    = mOnSend;

            addSession(newSession);
            newSession->start();
            mSocket = TCP::socket(mIoService);
        }
        doAccept();
    });
}

void Server::addSession(const SessionPtr& session) {
    mSessions.insert(session);
}

void Server::removeSession(const Server::SessionPtr& session) {
    mSessions.erase(session);
}


} //net
} //trek
