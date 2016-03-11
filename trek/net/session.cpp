#include "session.hpp"
#include "controller.hpp"

#include <trek/common/stringbuilder.hpp>

namespace trek {
namespace net {

using nlohmann::json;
using std::string;
using std::array;
using std::exception;

Session::Session(const Controllers& controllers, TCP::socket&& socket)
	: mControllers(controllers),
	  mSocket(std::move(socket)) { }

void Session::run() {
	mOnStart(*this);
	recv();
}

std::string Session::getRemoteAddress() const {
	return mSocket.remote_endpoint().address().to_string();
}

const Session::MessageCallback& Session::onRecv() {
	return mOnRecv;
}

const Session::MessageCallback& Session::onSend() {
	return mOnSend;
}

const Session::StatusCallback& Session::onStart() {
	return mOnStart;
}

const Session::StatusCallback& Session::onClose() {
	return mOnClose;
}

const Session::DestroyCallback& Session::onDestroy() {
	return mOnDestroy;
}

void Session::recv() {
	mSocket.async_receive(boost::asio::buffer(mBuffer), [this](const auto & errCode, auto length) {
		if(errCode) {
			mOnClose(*this);
			this->mOnDestroy(this->shared_from_this());
			return;
		}
		string rawRequset(mBuffer.data(), length);
		mOnRecv(*this, rawRequset);
		try {
			Request request(rawRequset);
			try {
				auto& controller = this->getController(request);
				auto response = controller.handleRequest(request);
				this->send(string(response));
			} catch(const exception& e) {
				this->send(string(Response{
					request.object,
					request.method,
					{e.what()},
					false
				}));
			}
		} catch(...) {
			this->send(string(Response{
				"unknown",
				"unknown",
				{"Invalid request"},
				false
			}));
		}

		this->recv();
	});
}

void Session::send(const std::string& response) {
	mSocket.async_send(boost::asio::buffer(response), [this, response](const auto & errCode, auto) {
		if(errCode) {
			mOnClose(*this);
			this->mOnDestroy(this->shared_from_this());
			return;
		}
		mOnSend(*this, response);
	});
}

Controller& Session::getController(const Request& request) {
	return *mControllers.at(request.object);
}

} //net
} //trek
