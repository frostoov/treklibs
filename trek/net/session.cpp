#include "session.hpp"
#include "controller.hpp"

#include <trek/common/stringbuilder.hpp>

#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>

namespace trek {
namespace net {

using nlohmann::json;

using boost::asio::async_read;
using boost::asio::async_write;
using boost::asio::buffer;

using std::string;
using std::array;
using std::exception;

Session::Session(const Controllers& controllers, TCP::socket&& socket)
	: mControllers(controllers),
	  mSocket(std::move(socket)),
	  mRemoteAddress(mSocket.remote_endpoint().address().to_string()) { }

void Session::run() {
	mOnStart(*this);
	recv();
}

std::string Session::getRemoteAddress() const {
	return mRemoteAddress;
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
	async_read(mSocket, buffer(&mMsgSize, sizeof(mMsgSize)), [this](auto &errCode, auto l) {
		if(errCode || sizeof(mMsgSize) != l) {
			mOnClose(*this);
			return mOnDestroy(shared_from_this());
		}
		mBuffer.resize(mMsgSize);
		msgRecv();
		recv();
	});
}

void Session::send(const string& response) {
	uint64_t length = response.size();
	async_write(mSocket, buffer(&length, sizeof(length)), [this, response](auto& errCode, auto l) {
		if(errCode || 8 != l) {
			mOnClose(*this);
			return mOnDestroy(shared_from_this());
		}
		msgSend(response);
	});
}

void Session::msgRecv() {
	async_read(mSocket, buffer(mBuffer), [&](auto &errCode, auto) {
		if(errCode) {
			mOnClose(*this);
			return mOnDestroy(shared_from_this());
		}
		auto request = string(mBuffer.data(), mBuffer.size());
		mOnRecv(*this, request);
		auto response = handleRequest(request);
		send(string(response));
	});
}

void Session::msgSend(const string& response) {
	async_write(mSocket, buffer(response.data(), response.size()), [this, response](auto& errCode, auto) {
		if(errCode) {
			mOnClose(*this);
			return mOnDestroy(shared_from_this());
		}
		mOnSend(*this, response);
	});
}

Response Session::handleRequest(const string& rawRequest) {
	try {
		Request request(rawRequest);
		try {
			auto& controller = *mControllers.at(request.object);
			auto response = controller.handleRequest(request);
			return string(response);
		} catch(const exception& e) {
			Response response{request.object, request.method, {e.what()}, false};
			return string(response);
		}
	} catch(...) {
		Response response{"unknown", "unknown", {"Invalid request"}, false};
		return string(response);
	}
}

} //net
} //trek
