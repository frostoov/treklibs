#include "server.hpp"

#include <trek/common/assertion.hpp>

namespace trek {
namespace net {

using std::runtime_error;
using std::string;
using std::exception;
using std::make_shared;

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

Server::ControllerMap Server::convertControllers(const Controllers& controllers) {
    ControllerMap controllerMap;
    for(const auto& c : controllers) {
        controllerMap.insert( {c->name(), c} );
    }
    return controllerMap;
}

void Server::doAccept() {
    mAcceptor.async_accept(mSocket, [this](const auto & errCode) {
        if(!errCode) {
            auto newSession = make_shared<Session> (mControllers, std::move(mSocket));

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
    if(mSessions.count(session) == 0)
        mSessions.insert(session);
    else
        throw Assertion("Server::addSession: session already exists");
}

void Server::removeSession(const Server::SessionPtr& session) {
    if(mSessions.count(session) != 0)
        mSessions.erase(session);
    else
        throw Assertion("Server::removeSession: session does not exists");
}


} //net
} //trek
