#include "server.hpp"

namespace trek {
namespace net {

using std::runtime_error;
using std::string;
using std::exception;
using std::make_shared;
using std::logic_error;

using boost::asio::ip::address;

Server::Server(const std::vector<ControllerPtr>& controllers, const string& ipAdrress, uint16_t port)
	: mControllers(convertControllers(controllers)),
	  mAcceptor(mIoService, TCP::endpoint(IpAddress::from_string(ipAdrress), port)),
	  mSocket(mIoService) { }

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
	if(mSessions.count(session) != 0)
		throw logic_error("Server::addSession: session already exists");
	mSessions.insert(session);
}

void Server::removeSession(const Server::SessionPtr& session) {
	mSessions.erase(session);
}

Server::Controllers Server::convertControllers(const std::vector<ControllerPtr>& controllers) {
	Controllers ret;
	for(auto c : controllers) {
		ret.insert({c->name(), c});
	}
	return ret;
}

} //net
} //trek
